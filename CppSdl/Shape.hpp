#pragma once

#include "../Algebra/Vector.h" 
#include "Ray.hpp"

namespace GL
{
	class Shape
	{
	public:
		//constructor and destructor
		Shape();

		virtual ~Shape();

		//function to test for intersections
		virtual bool TestIntersection(const Ray& castRay, Vector<double>& intPoint, Vector<double>& localNormal, Vector<double>& localColor);

		//function to test whether 2 floating-point numbers are close to being equal
		bool CloseEnough(const double f1, const double f2);

		//public member variables:
	public:
		//the base color of the object
		Vector<double> _baseColor;

	};

}

