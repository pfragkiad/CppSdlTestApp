#include "Sphere.hpp"

GL::Sphere::Sphere()
{
}

GL::Sphere::~Sphere()
{
}

bool GL::Sphere::TestIntersection(const Ray& castRay, Vector<double>& intPoint, Vector<double>& localNormal, Vector<double>& localColor)
{
	//compute the values of a, b, c

	Vector<double> vhat = !castRay._lab;

	//note that a is equal to the squared magnitude of the direction of the case ray.
	//as this iwll be a unit vector, we can conclude that the value of 'a' will always be 1
	//a = 1.0;
	
	//calculate b
	double b = 2.0 * (castRay._point1 * vhat);
	
	//calculate c
	double c = castRay._point1 * castRay._point1 - 1.0;

	//test whether we actually have an intersection!
	double intTest = b * b - 4.0 * c;
	return intTest > 0.0;
}
