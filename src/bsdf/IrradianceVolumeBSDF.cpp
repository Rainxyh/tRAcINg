#include <bsdf\IrradianceVolumeBSDF.hpp>
#include <core\Frame.hpp>
#include <core\Sampling.hpp>
#include <core\Texture.hpp>

NAMESPACE_BEGIN

REGISTER_CLASS(IrradianceVolumeBSDF, XML_BSDF_IRRADIANCEVOLUME);

IrradianceVolumeBSDF::IrradianceVolumeBSDF(const PropertyList &PropList)
{
}

IrradianceVolumeBSDF::~IrradianceVolumeBSDF()
{
}

float fract(float x)
{
    return x - floor(x);
}

Vector2f fract(Vector2f x)
{
    return Vector2f(fract(x[0]), fract(x[1]));
}

Vector3f fract(Vector3f x)
{
    return Vector3f(fract(x[0]), fract(x[1]), fract(x[2]));
}

Vector2f hash(Vector2f p)
{
    GetCoreCount();
    // p = mod(p, 4.0); // tile
    p = Vector2f(p.dot(Vector2f(127.1, 311.7)),
                 p.dot(Vector2f(269.5, 183.3)));
    return fract(Vector2f(sin(p[0]) * 18.5453, sin(p[1]) * 18.5453));
}

// return distance, and cell id
Vector2f voronoi(Vector2f x)
{
    Vector2f n = Vector2f(floor(x[0]), floor(x[1]));
    Vector2f f = fract(x);

    Vector3f m = Vector3f(8.0);
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
        {
            Vector2f g = Vector2f(float(i), float(j));
            Vector2f o = hash(n + g);
            Vector2f r = g - f + o;
            float d = r.dot(r);
            if (d < m[0])
                m = Vector3f(d, o[0], o[1]);
        }

    return Vector2f(sqrt(m[0]), m[1] + m[2]);
}

Vector3f sigmoid(Vector3f x)
{
    return Vector3f(1 / (1 + exp(-x[0])), 1 / (1 + exp(-x[1])), 1 / (1 + exp(-x[2])));
}

bool border(Vector3f pos, float threshold)
{
    if ((fract(pos[0]) < threshold) ||
        (fract(pos[1]) < threshold) ||
        (fract(pos[2]) < threshold))
        return true;
    return false;
}

bool center(Vector3f pos, float radius)
{
    Vector3f frac = fract(pos);
    int cnt = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = i + 1; j < 3; ++j)
        {
            Vector2f dis = Vector2f(frac[i], frac[j]) - Vector2f(0.5, 0.5);
            if (dis.norm() < radius)
                return true;
        }
    }
    return false;
}

Color3f getColor(Vector3f pos, int steps)
{
    pos *= steps;
    if (border(pos, 3e-2))
        return BLACK;
    if (center(pos, 5e-2))
        return RED;
    Color3f col = Color3f(
        (int)pos[0] / (float)steps,
        (int)pos[1] / (float)steps,
        (int)pos[2] / (float)steps);
    return col;
}

Color3f IrradianceVolumeBSDF::Sample(BSDFQueryRecord &Record, const Point2f &Sample) const
{
    int cnt = 20;
    Vector3f pos = Record.Isect.P;
    pos = sigmoid(pos);
    // return getColor(pos, cnt);
    
    Vector3f normal = pos;
    float CosThetaI = normal.y();
    float CosPhiI = normal.x();
    float theta = SafeAcos(CosThetaI)*180/M_PI;
    float phi = SafeAcos(CosPhiI)*180/M_PI;
    if (theta > 60)return GREEN;
    float delta = M_PI / 10;
    if (fabs(theta - M_PI/2) < delta)return RED;
    if (fabs(phi - M_PI / 2) < delta)return BLACK;
    return WHITE;

    Vector2f c = voronoi( (14.0+6.0*sin(0.2))* Vector2f(pos[2], pos[1]));
    Vector3f col = Vector3f(0.5) + 0.5 * Vector3f(cos(c[1] * 6.2831), cos(1.0 + c[1] * 6.2831), cos(2.0 + c[1] * 6.2831));
    return Color3f(col[0], col[1], col[2]);
    // Vector3f t = (Record.Wi + Vector3f(1.0)) / 2.;
    // t *= cnt;
    // return Color3f((int)t[0]/(float)cnt, (int)t[1]/(float)cnt, (int)t[2]/(float)cnt);

    // return Color3f((int)level[0]/(float)cnt, (int)level[1]/(float)cnt, 0);
}

Color3f IrradianceVolumeBSDF::Eval(const BSDFQueryRecord &Record) const
{
    return BLACK;
}

float IrradianceVolumeBSDF::Pdf(const BSDFQueryRecord &Record) const
{
    return 1.0;
}

bool IrradianceVolumeBSDF::IsIrradianceVolume() const
{
    return true;
}

void IrradianceVolumeBSDF::AddChild(Object *pChildObj, const std::string &Name)
{
}

void IrradianceVolumeBSDF::Activate()
{
}

std::string IrradianceVolumeBSDF::ToString() const
{
    return "IrradianceVolume[]";
}
NAMESPACE_END
