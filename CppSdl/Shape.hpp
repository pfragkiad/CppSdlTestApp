#pragma once

#include "../Algebra/Algebra.h" 
#include "Ray.hpp"
#include "Transform.hpp"
#include "IntersectionInfo.h"
#include <memory>

namespace GL
{

	class Shape
	{
	public:
		//constructor and destructor
		Shape();

		//useful for static images
		Shape(VD baseColor);

		Shape(VD baseColor, Transform transformMatrix);

		virtual ~Shape();

		//function to test for intersections
		//virtual bool TestIntersection(const Ray& castRay, VD& intersectionPoint, VD& localNormal, VD& localColor);
		virtual IntersectionInfo TestIntersection(const Ray& castRay) const;

		//function to set the transform matrix
		void SetTransformMatrix(const Transform& transform);

		//function to test whether 2 floating-point numbers are close to being equal
		bool CloseEnough(const double f1, const double f2);

		//public member variables:
	public:
		//the base color of the object
		VD _baseColor;

		//geometric transform applied to the object
		Transform _transformMatrix;
	};

}

//they must be declared after the class definition!
typedef std::shared_ptr<GL::Shape> pShape;
typedef std::vector<pShape> pShapesVector;