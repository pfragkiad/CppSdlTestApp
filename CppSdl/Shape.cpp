#include "Shape.hpp"

#include <cmath>

#define EPSILON 1e-21f

GL::Shape::Shape()
{
}

GL::Shape::~Shape()
{
}

bool GL::Shape::TestIntersection(const Ray& castRay, Vector<double>& intPoint, Vector<double>& localNormal, Vector<double>& localColor)
{
    return false;
}

void GL::Shape::SetTransformMatrix(const Transform& transform)
{
    _transformMatrix = transform;
}

bool GL::Shape::CloseEnough(const double f1, const double f2)
{
    return fabs(f1-f2)<EPSILON;
}
