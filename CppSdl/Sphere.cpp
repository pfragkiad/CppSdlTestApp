#include "Sphere.hpp"

GL::Sphere::Sphere()
{
}

GL::Sphere::~Sphere()
{
}

//bool GL::Sphere::TestIntersection(const Ray& castRay, VD& intersectionPoint, VD& localNormal, VD& localColor)
GL::IntersectionInfo GL::Sphere::TestIntersection(const Ray& castRay) const
{
	//castRay is in the world coordinate system
	//we transform it in the local coordinate system of the sphere!
	//APPLY THE BACKWARDS TRANSFORM because we go from WORLD -> LOCAL!
	Ray bckRay = _transformMatrix.Apply(castRay, false);

	//compute the values of a, b, c

	VD vhat = !bckRay.GetLab();

	//note that a is equal to the squared magnitude of the direction of the case ray.
	//as this iwll be a unit vector, we can conclude that the value of 'a' will always be 1
	//a = 1.0;

	//calculate b
	double b = 2.0 * bckRay.GetPoint1() * vhat;

	//calculate c
	//double c = bckRay.GetPoint1() * bckRay.GetPoint1() - 1.0;
	double c = bckRay.GetPoint1().LengthSquared() - 1.0;

	//test whether we actually have an intersection!
	double discriminant = b * b - 4.0 * c;

	VD poi; //point of intersection

	bool tested = discriminant >= 0.0;
	if (!tested) 
		//return false;
		return GL::IntersectionInfo(); //return empty (= false tested)

	double sqr = sqrt(discriminant);
	double t1 = (-b + sqr) / 2.0;
	double t2 = (-b - sqr) / 2.0;

	//if either t1 or t2 are negative, then at least part of the object is 
	//behind the camera and so we will ignore it
	if (t1 < 0.0 || t2 < 0.0) 
		//return false;
		return GL::IntersectionInfo(); //return empty (= false tested)

	//determine which point of intersection was closest to the camera!
	//t1 is closest to the camera (we are not interested in t2)
	poi = bckRay.GetPoint1() + vhat * (t1 < t2 ? t1 : t2);
	//if (t1 < t2) 
	//	poi = bckRay._point1 + vhat * t1;
	//else
	//	poi = bckRay._point1 + vhat * t2;

	//transform the intersection point back into world coordinates!
	VD intersectionPoint = _transformMatrix.Apply(poi, true);

	VD objOrigin = VDs::Zero;
	VD newObjOrigin = _transformMatrix.Apply(objOrigin, true);

	//compute the local normal
	VD localNormal = !(intersectionPoint - newObjOrigin);

	//return the base color
	VD localColor = _baseColor;

	//return true;
	return IntersectionInfo(intersectionPoint, localNormal, localColor);
}
