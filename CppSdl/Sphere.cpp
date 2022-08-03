#include "Sphere.hpp"

GL::Sphere::Sphere()
{
}

GL::Sphere::~Sphere()
{
}

bool GL::Sphere::TestIntersection(const Ray& castRay, VectorD& intersectionPoint, VectorD& localNormal, VectorD& localColor)
{
	//compute the values of a, b, c

	VectorD vhat = !castRay._lab;

	//note that a is equal to the squared magnitude of the direction of the case ray.
	//as this iwll be a unit vector, we can conclude that the value of 'a' will always be 1
	//a = 1.0;
	
	//calculate b
	double b = 2.0 * (castRay._point1 * vhat);
	
	//calculate c
	double c = castRay._point1 * castRay._point1 - 1.0;

	//test whether we actually have an intersection!
	double intTest = b * b - 4.0 * c;
	bool tested =  intTest >= 0.0;
	if (!tested) return false;

	double sqr = sqrt(intTest);
	double t1 = (-b + sqr) / 2.0;
	double t2 = (-b - sqr) / 2.0;

	//if either t1 or t2 are negative, then at least part of the object is 
	//behind the camera and so we will ignore it
	if (t1 < 0.0 || t2 < 0.0) return false;

	//determine which point of intersection was closest to the camera!
	if (t1 < t2) //t1 is closest to the camera (we are not interested in t2)
		intersectionPoint = castRay._point1 + vhat * t1;
	else
		intersectionPoint = castRay._point1 + vhat * t2;

	//compute the local normal
	localNormal = !intersectionPoint;
 
	return true;
}
