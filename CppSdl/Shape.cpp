#include "Shape.hpp"

#include <cmath>

#define EPSILON 1e-21f

GL::Shape::Shape()
{
}

GL::Shape::Shape(VD baseColor):_baseColor(baseColor)
{
}

GL::Shape::Shape(VD baseColor, Transform transformMatrix) :
	_baseColor(baseColor), _transformMatrix(transformMatrix)

{
}

GL::Shape::~Shape()
{
}

//bool TestIntersection(const Ray& castRay, VectorD& intPoint, VectorD& localNormal, VectorD& localColor)

//bool GL::Shape::TestIntersection(const Ray& castRay, VD& intPoint, VD& localNormal, VD& localColor)
//{
//	return false;
//}

GL::IntersectionInfo GL::Shape::TestIntersection(const Ray& castRay) const
{
	return GL::IntersectionInfo();
}

void GL::Shape::SetTransformMatrix(const Transform& transform)
{
	_transformMatrix = transform;
}

bool GL::Shape::CloseEnough(const double f1, const double f2)
{
	return fabs(f1 - f2) < EPSILON;
}
