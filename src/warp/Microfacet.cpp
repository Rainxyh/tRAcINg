#include <core\BSDF.hpp>
#include <core\Frame.hpp>
#include <warp\Warp.hpp>

NAMESPACE_BEGIN

class Microfacet : public BSDF {
public:
    Microfacet(const PropertyList &propList) {
        /* RMS surface roughness */
        m_alpha = propList.GetFloat("alpha", 0.1f);

        /* Interior IOR (default: BK7 borosilicate optical glass) */
        m_intIOR = propList.GetFloat("intIOR", 1.5046f);

        /* Exterior IOR (default: air) */
        m_extIOR = propList.GetFloat("extIOR", 1.000277f);

        /* Albedo of the diffuse base material (a.k.a "kd") */
        m_kd = propList.GetColor("kd", Color3f(0.5f));

        /* To ensure energy conservation, we must scale the 
           specular component by 1-kd. 

           While that is not a particularly realistic model of what 
           happens in reality, this will greatly simplify the 
           implementation. Please see the course staff if you're 
           interested in implementing a more realistic version 
           of this BRDF. */
        m_ks = 1 - m_kd.maxCoeff();
    }
/*---------------------------------------------------------------------------------------------------------------------------------------------*/
    static float DistributeBeckmann(const Vector3f &wh, float alpha)
    { // Beckmann normal distribution term
        float tanTheta = Frame::TanTheta(wh);
        float CosTheta = Frame::CosTheta(wh);
        float a = std::exp(-(tanTheta * tanTheta) / (alpha * alpha));
        float b = M_PI * alpha * alpha * std::pow(CosTheta, 4.0f);
        return a / b;
    }
/*---------------------------------------------------------------------------------------------------------------------------------------------*/
    static float smithBeckmannG1(const Vector3f &wv, const Vector3f &wh, float alpha)
    { // Beckmann geometric masking term
        float c = wv.dot(wh) / Frame::CosTheta(wv);
        if (c <= 0) return 0;
        float b = 1.0f / (alpha * Frame::TanTheta(wv));
        return b < 1.6f ? (3.535f * b + 2.181f * b * b) / (1.f + 2.276f * b + 2.577f * b * b) : 1;
    }
/*---------------------------------------------------------------------------------------------------------------------------------------------*/
    /// Evaluate the BRDF for the given pair of directions
	virtual Color3f Eval(const BSDFQueryRecord &bRec) const {

		// if (bRec.measure != ESolidAngle) return BLACK;
        if (Frame::CosTheta(bRec.Wi) <= 0 || Frame::CosTheta(bRec.Wo) <= 0)
			return BLACK;

		Color3f diffuse = m_kd * INV_PI;

		Normal3f wh = (bRec.Wi + bRec.Wo).normalized();
		float D = DistributeBeckmann(wh, m_alpha);
		float F = Fresnel(wh.dot(bRec.Wi), m_extIOR, m_intIOR);
		float G = smithBeckmannG1(bRec.Wi, wh, m_alpha) * smithBeckmannG1(bRec.Wo, wh, m_alpha);

		Color3f specular = m_ks * D * F * G / (4 * (Frame::CosTheta(bRec.Wi) * Frame::CosTheta(bRec.Wo)));
		if (!specular.IsValid()) specular = BLACK;
		return specular + diffuse;
	}
/*---------------------------------------------------------------------------------------------------------------------------------------------*/
    /// Evaluate the sampling density of \ref sample() wrt. solid angles
    virtual float Pdf(const BSDFQueryRecord &bRec) const {
		
		if (Frame::CosTheta(bRec.Wo) <= 0.0f || Frame::CosTheta(bRec.Wi) <= 0.0f) return 0.0f;
		
		float dpdf = (1.0f - m_ks) * Warp::squareToCosineHemispherePdf(bRec.Wo);
		Normal3f wh = (bRec.Wi + bRec.Wo).normalized();
        /* The microsurface model samples the direction of the normal h of the microsurface, and 
           the solid angle element of the probability density is the hemisphere determined relative to the normal h of the microsurface, 
           rather than the hemisphere determined by the normal n of the macroscopic surface, 
           so the probability reflection projection from the normal of the microsurface When the light probability is obtained, 
           it needs to be multiplied by the corresponding Jacobian matrix determinant. */
		float jacobian = 0.25f / (wh.dot(bRec.Wo));
		float spdf = m_ks * Warp::squareToBeckmannPdf(wh, m_alpha) * jacobian;
		if (isnan(dpdf)) dpdf = 0.0f;
		if (isnan(spdf)) spdf = 0.0f;
		return dpdf + spdf;
    }
/*---------------------------------------------------------------------------------------------------------------------------------------------*/
    /// Sample the BRDF
    Color3f Sample(BSDFQueryRecord &bRec, const Point2f &_sample) const
    {
        if (Frame::CosTheta(bRec.Wi) <= 0)
        {
            return BLACK;
        }
        if (_sample.x() > m_ks)
        { // diffuse
            Point2f sample((_sample.x() - m_ks) / (1.f - m_ks), _sample.y());
            bRec.Wo = Warp::squareToCosineHemisphere(sample);
        }
        else
        { // specular
            Point2f sample(_sample.x() / m_ks, _sample.y());
            Vector3f wh = Warp::squareToBeckmann(sample, m_alpha);
            bRec.Wo = ((2.0f * wh.dot(bRec.Wi) * wh) - bRec.Wi).normalized();
        }
        if (bRec.Wo.z() < 0.f)
        {
            return BLACK;
        }
        // Note: Once you have implemented the part that computes the scattered
        // direction, the last part of this function should simply return the
        // BRDF value divided by the solid angle density and multiplied by the
        // cosine factor from the reflection equation, i.e.
        return Eval(bRec) / Pdf(bRec) * Frame::CosTheta(bRec.Wo);
    }
    Color3f Sample(BSDFQueryRecord& bRec, Sampler* sampler) const {
        return Sample(bRec, sampler->Next2D());
    }
/*---------------------------------------------------------------------------------------------------------------------------------------------*/
    bool isDiffuse() const {
        /* While microfacet BRDFs are not perfectly diffuse, they can be
           handled by sampling techniques for diffuse/non-specular materials,
           hence we return true here */
        return true;
    }
/*---------------------------------------------------------------------------------------------------------------------------------------------*/
    std::string ToString() const {
        return tfm::format(
            "Microfacet[\n"
            "  alpha = %f,\n"
            "  intIOR = %f,\n"
            "  extIOR = %f,\n"
            "  kd = %s,\n"
            "  ks = %f\n"
            "]",
            m_alpha,
            m_intIOR,
            m_extIOR,
            m_kd.ToString(),
            m_ks
        );
    }
    
private:
    float m_alpha;
    float m_intIOR, m_extIOR;
    float m_ks;
    Color3f m_kd;
};

REGISTER_CLASS(Microfacet, "XML_WARP_MICROFACET");
NAMESPACE_END
