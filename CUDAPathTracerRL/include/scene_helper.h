#ifndef _SCENE_HELPER_H
#define _SCENE_HELPER_H

#include "material.h"
#include "sphere.h"
#include "world.h"

void setupScene1(World *world)
{
    auto *mPlane = new Material(world);
    mPlane->color = Color(0.9, 0.9, 0.9);
    mPlane->kr = 0;
    auto *mPlane2 = new Material(world);
    mPlane2->color = Color(0.9, 0.2, 0.3);
    mPlane2->kr = 0;
    auto *mPlane3 = new Material(world);
    mPlane3->color = Color(0.1, 0.3, 0.9);
    mPlane3->kr = 0;
    auto *mPlane4 = new Material(world);
    mPlane4->color = Color(0.1, 0.9, 0.2);
    mPlane4->kr = 0;
    auto *glass = new Material(world); // dielectric
    glass->color = Color(1, 0.95, 0.95);
    glass->eta = 1.25;
    glass->kt = 1;
    auto *glass2 = new Material(world); // dielectric
    glass2->color = Color(1, 0.95, 0.95);
    glass2->eta = 1.8;
    glass2->kt = 1;
    auto *glossy = new Material(world); // glossy
    glossy->color = Color(1, 1, 0.23);
    glossy->n = 20;
    auto *mirror = new Material(world); // mirror
    mirror->color = Color(0.8, 1, 0.9);
    mirror->kr = 0.8;
    auto *polished = new Material(world); // mirror
    polished->color = Color(1, 0.8, 0.9);
    polished->kr = 0.13;

    world->addObject(new Sphere(Vector3D(2, -3, 0), 2, glass2));
    world->addObject(new Sphere(Vector3D(-4, -3, 0), 0.98, glass));
    world->addObject(new Sphere(Vector3D(-2, -1, 0), 1.23, polished));
    world->addObject(new Sphere(Vector3D(1, 2, -2), 1.5, glossy));

    world->addObject(new Sphere(Vector3D(0, -2006, 0), 2000, mPlane));  // down
    world->addObject(new Sphere(Vector3D(0, 2010, 0), 2000, mPlane));   // up
    world->addObject(new Sphere(Vector3D(2009, 0, 0), 2000, mPlane3));  // right
    world->addObject(new Sphere(Vector3D(-2009, 0, 0), 2000, mPlane2)); // left
    world->addObject(new Sphere(Vector3D(0, 0, -2012), 2000, mPlane4)); // front
    world->addObject(new Sphere(Vector3D(0, 0, 2016), 2000, mPlane4));  // back

    world->addLight(new PointLightSource(world, Vector3D(0, 11, 0), Color(5, 5, 5)), 4);
    world->addLight(new PointLightSource(world, Vector3D(4.1, 0, 0), Color(4, 1, 1)), 1.5);
    world->addLight(new PointLightSource(world, Vector3D(0, -0.5, 0), Color(1, 4.5, 3)), 0.7);
}

void setupScene2(World *world)
{
    auto *mPlane = new Material(world);
    mPlane->color = Color(0.9, 0.9, 0.9);
    mPlane->kr = 0;
    auto *mPlane2 = new Material(world);
    mPlane2->color = Color(0.9, 0.2, 0.3);
    mPlane2->kr = 0;
    auto *mPlane3 = new Material(world);
    mPlane3->color = Color(0.1, 0.3, 0.9);
    mPlane3->kr = 0;
    auto *mPlane4 = new Material(world);
    mPlane4->color = Color(0.8, 1.5, 0.2);
    mPlane4->kr = 0;
    auto *glass = new Material(world); // dielectric
    glass->color = Color(1, 0.95, 0.95);
    glass->eta = 1.25;
    glass->kt = 1;
    auto *glass2 = new Material(world); // dielectric
    glass2->color = Color(1, 0.95, 0.95);
    glass2->eta = 1.8;
    glass2->kt = 1;
    auto *glassRed = new Material(world); // dielectric
    glassRed->color = Color(1, 0.5, 0.6);
    glassRed->eta = 1.8;
    glassRed->kt = 1;
    auto *glossy = new Material(world); // glossy
    glossy->color = Color(1, 1, 0.23);
    glossy->n = 20;
    auto *mirror = new Material(world); // mirror
    mirror->color = Color(0.8, 1, 0.9);
    mirror->kr = 0.8;
    auto *polished = new Material(world); // mirror
    polished->color = Color(1, 0.8, 0.9);
    polished->kr = 0.13;

    world->addObject(new Sphere(Vector3D(0, -3.5, 0), 1.5, glass2));
    world->addObject(new Sphere(Vector3D(0, -0.35, 0), 1.2, glass2));
    world->addObject(new Sphere(Vector3D(0, 2.2, 0), 0.9, glass2));
    world->addObject(new Sphere(Vector3D(0, 4.3, 0), 0.65, glassRed));

    world->addObject(new Sphere(Vector3D(0, -2006, 0), 2000, mPlane4)); // down
    world->addObject(new Sphere(Vector3D(0, 2010, 0), 2000, mPlane));   // up
    world->addObject(new Sphere(Vector3D(2009, 0, 0), 2000, mPlane3));  // right
    world->addObject(new Sphere(Vector3D(-2009, 0, 0), 2000, mPlane2)); // left
    world->addObject(new Sphere(Vector3D(0, 0, -2012), 2000, mPlane));  // front
    world->addObject(new Sphere(Vector3D(0, 0, 2016), 2000, mPlane4));  // back

    world->addLight(new PointLightSource(world, Vector3D(0, 8.5, 0), Color(4, 4, 4)), 1.8);
}

void setupScene3(World *world)
{
    auto *mPlane = new Material(world);
    mPlane->color = Color(0.9, 0.9, 0.9);
    mPlane->kr = 0;
    auto *mPlane2 = new Material(world);
    mPlane2->color = Color(0.9, 0.2, 0.3);
    mPlane2->kr = 0;
    auto *mPlane3 = new Material(world);
    mPlane3->color = Color(0.1, 0.3, 0.9);
    mPlane3->kr = 0;
    auto *mPlane4 = new Material(world);
    mPlane4->color = Color(0.1, 0.9, 0.2);
    mPlane4->kr = 0;
    auto *glass = new Material(world); // dielectric
    glass->color = Color(1, 0.95, 0.95);
    glass->eta = 1.25;
    glass->kt = 1;
    auto *glass2 = new Material(world); // dielectric
    glass2->color = Color(1, 0.95, 0.95);
    glass2->eta = 1.8;
    glass2->kt = 1;
    auto *glassRed = new Material(world); // dielectric
    glassRed->color = Color(1, 0.5, 0.6);
    glassRed->eta = 1.8;
    glassRed->kt = 1;
    auto *glossy = new Material(world); // glossy
    glossy->color = Color(1, 1, 0.23);
    glossy->n = 20;
    auto *mirror = new Material(world); // mirror
    mirror->color = Color(0.8, 1, 0.9);
    mirror->kr = 0.8;
    auto *polished = new Material(world); // mirror
    polished->color = Color(1, 0.8, 0.9);
    polished->kr = 0.13;

    //    world->addObject(new Sphere(Vector3D(2, -3.5, 0), 1.5, mPlane4));
    //    world->addObject(new Sphere(Vector3D(2, -0.35, 0), 1.2, mPlane3));
    //    world->addObject(new Sphere(Vector3D(2, 2.2, 0), 0.9, mPlane));
    //    world->addObject(new Sphere(Vector3D(2, 4.3, 0), 0.65, mPlane2));

    world->addObject(new Sphere(Vector3D(-6, 0, 0), 4, mPlane2));
    world->addObject(new Sphere(Vector3D(-5, 0, 0), 4, mPlane2));
    world->addObject(new Sphere(Vector3D(-4, 0, 0), 4, mPlane2));
    world->addObject(new Sphere(Vector3D(-3, 0, 0), 4, mPlane2));
    world->addObject(new Sphere(Vector3D(-2, 0, 0), 4, mPlane2));
    world->addObject(new Sphere(Vector3D(-1, 0, 0), 4, mPlane2));
    world->addObject(new Sphere(Vector3D(-0, 0, 0), 4, mPlane2));
    world->addObject(new Sphere(Vector3D(1, 0, 0), 4, mPlane2));
    world->addObject(new Sphere(Vector3D(2, 0, 0), 4, mPlane2));
    world->addObject(new Sphere(Vector3D(3, 0, 0), 4, mPlane2));
    world->addObject(new Sphere(Vector3D(4, 0, 0), 4, mPlane2));
    world->addObject(new Sphere(Vector3D(5, 0, 0), 4, mPlane2));
    world->addObject(new Sphere(Vector3D(6, 0, 0), 4, mPlane2));

    world->addObject(new Sphere(Vector3D(-4.2, -5, 1), 0.5, mPlane4));
    world->addObject(new Sphere(Vector3D(5, 4, 3), 0.5, mPlane2));

    world->addObject(new Sphere(Vector3D(0, -2006, 0), 2000, mPlane));  // down
    world->addObject(new Sphere(Vector3D(0, 2010, 0), 2000, mPlane4));  // up
    world->addObject(new Sphere(Vector3D(2009, 0, 0), 2000, mPlane3));  // right
    world->addObject(new Sphere(Vector3D(-2009, 0, 0), 2000, mPlane2)); // left
    world->addObject(new Sphere(Vector3D(0, 0, -2012), 2000, mPlane));  // front
    world->addObject(new Sphere(Vector3D(0, 0, 2016), 2000, mPlane4));  // back

    world->addLight(new PointLightSource(world, Vector3D(2, 10, 0), Color(15, 15, 15)), 3);
}

void setupScene4(World *world)
{
    auto *mPlane = new Material(world);
    mPlane->color = Color(0.9, 0.9, 0.9);
    mPlane->kr = 0;
    auto *mPlane2 = new Material(world);
    mPlane2->color = Color(0.9, 0.2, 0.3);
    mPlane2->kr = 0;
    auto *mPlane3 = new Material(world);
    mPlane3->color = Color(0.1, 0.3, 1.1);
    mPlane3->kr = 0;
    auto *mPlane4 = new Material(world);
    mPlane4->color = Color(0.1, 0.9, 0.2);
    mPlane4->kr = 0;
    auto *glass = new Material(world); // dielectric
    glass->color = Color(1, 0.95, 0.95);
    glass->eta = 1.25;
    glass->kt = 1;
    auto *glass2 = new Material(world); // dielectric
    glass2->color = Color(1, 0.95, 0.95);
    glass2->eta = 1.8;
    glass2->kt = 1;
    auto *glassRed = new Material(world); // dielectric
    glassRed->color = Color(1, 0.5, 0.6);
    glassRed->eta = 1.8;
    glassRed->kt = 1;
    auto *glossy = new Material(world); // glossy
    glossy->color = Color(1, 1, 0.23);
    glossy->n = 20;
    auto *mirror = new Material(world); // mirror
    mirror->color = Color(0.8, 1, 0.9);
    mirror->kr = 0.8;
    auto *polished = new Material(world); // mirror
    polished->color = Color(1, 0.8, 0.9);
    polished->kr = 0.13;

    //    world->addObject(new Sphere(Vector3D(2, -3.5, 0), 1.5, glass2));
    //    world->addObject(new Sphere(Vector3D(2, -0.35, 0), 1.2, glass2));
    //    world->addObject(new Sphere(Vector3D(2, 2.2, 0), 0.9, glass2));
    //    world->addObject(new Sphere(Vector3D(2, 4.3, 0), 0.65, glassRed));

    world->addObject(new Sphere(Vector3D(0, -4, -5), 3.1, mPlane2));

    //    world->addObject(new Sphere(Vector3D(-4.2, -4, 1), 0.5, mPlane4));
    //    world->addObject(new Sphere(Vector3D(0, 1, 0), 2, mPlane4));

    //    world->addObject(new Sphere(Vector3D(0, -2006, 0), 2000, mPlane)); //down
    //    world->addObject(new Sphere(Vector3D(0, 2010, 0), 2000, mPlane4)); //up
    //    world->addObject(new Sphere(Vector3D(2009, 0, 0), 2000, mPlane3)); //right
    //    world->addObject(new Sphere(Vector3D(-2009, 0, 0), 2000, mPlane2)); //left
    //    world->addObject(new Sphere(Vector3D(0, 0, -2012), 2000, mPlane)); //front
    //    world->addObject(new Sphere(Vector3D(0, 0, 2016), 2000, mPlane4)); //back

    //    world->addLight(new PointLightSource(world, Vector3D(2, 16, 0), Color(9, 9, 9)), 8);
    //    world->addLight(new PointLightSource(world, Vector3D(-0.5, 4, -3), Color(9, 9, 9)), 1);
    world->addLight(new PointLightSource(world, Vector3D(2, 3, 0), Color(50, 50, 50)), 0.5);
    //    world->addLight(new PointLightSource(world, Vector3D(-5.5, 7, -3), Color(9, 9, 9)), 1);
    //    world->addLight(new PointLightSource(world, Vector3D(4.1, 0, 0), Color(4, 1, 2)), 1.5);
    //    world->addLight(new PointLightSource(world, Vector3D(0, -0.5, 0), Color(2, 7, 3)), 0.7);;
}

void setupScene5(World *world)
{
    auto *mPlane = new Material(world);
    mPlane->color = Color(0.9, 0.9, 0.9);
    mPlane->kr = 0;
    auto *mPlane2 = new Material(world);
    mPlane2->color = Color(0.9, 0.2, 0.3);
    mPlane2->kr = 0;
    auto *mPlane3 = new Material(world);
    mPlane3->color = Color(0.1, 0.3, 0.9);
    mPlane3->kr = 0;
    auto *mPlane4 = new Material(world);
    mPlane4->color = Color(0.1, 0.9, 0.2);
    mPlane4->kr = 0;
    auto *glass = new Material(world); // dielectric
    glass->color = Color(1, 0.95, 0.95);
    glass->eta = 1.25;
    glass->kt = 1;
    auto *glass2 = new Material(world); // dielectric
    glass2->color = Color(1, 0.95, 0.95);
    glass2->eta = 1.8;
    glass2->kt = 1;
    auto *glassRed = new Material(world); // dielectric
    glassRed->color = Color(1, 0.5, 0.6);
    glassRed->eta = 1.8;
    glassRed->kt = 1;
    auto *glossy = new Material(world); // glossy
    glossy->color = Color(1, 1, 0.23);
    glossy->n = 20;
    auto *mirror = new Material(world); // mirror
    mirror->color = Color(0.8, 1, 0.9);
    mirror->kr = 0.8;
    auto *polished = new Material(world); // mirror
    polished->color = Color(1, 0.8, 0.9);
    polished->kr = 0.13;

    world->addObject(new Sphere(Vector3D(2, -3.5, 0), 1.5, glass2));
    world->addObject(new Sphere(Vector3D(2, -0.35, 0), 1.2, glass2));
    world->addObject(new Sphere(Vector3D(2, 2.2, 0), 0.9, glass2));
    world->addObject(new Sphere(Vector3D(2, 4.3, 0), 0.65, glassRed));

    world->addObject(new Sphere(Vector3D(-3.5, -1, 0), 3.1, mPlane));

    world->addObject(new Sphere(Vector3D(-4.2, -4, 1), 0.5, glassRed));
    world->addObject(new Sphere(Vector3D(5, 4, 3), 0.5, mPlane3));

    world->addObject(new Sphere(Vector3D(0, -2006, 0), 2000, mPlane));  // down
    world->addObject(new Sphere(Vector3D(0, 2010, 0), 2000, mPlane4));  // up
    world->addObject(new Sphere(Vector3D(2009, 0, 0), 2000, mPlane3));  // right
    world->addObject(new Sphere(Vector3D(-2009, 0, 0), 2000, mPlane2)); // left
    world->addObject(new Sphere(Vector3D(0, 0, -2012), 2000, mPlane));  // front
    world->addObject(new Sphere(Vector3D(0, 0, 2016), 2000, mPlane4));  // back

    //    world->addLight(new PointLightSource(world, Vector3D(2, 16, 0), Color(9, 9, 9)), 8);
    //    world->addLight(new PointLightSource(world, Vector3D(-0.5, 4, -3), Color(9, 9, 9)), 1);
    world->addLight(new PointLightSource(world, Vector3D(-3.5, 3.5, 0), Color(10, 10, 10)), 1);
    //    world->addLight(new PointLightSource(world, Vector3D(-5.5, 7, -3), Color(9, 9, 9)), 1);
    //    world->addLight(new PointLightSource(world, Vector3D(4.1, 0, 0), Color(4, 1, 2)), 1.5);
    //    world->addLight(new PointLightSource(world, Vector3D(0, -0.5, 0), Color(2, 7, 3)), 0.7);
}

#endif //_SCENE_HELPER_H
