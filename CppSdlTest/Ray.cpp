#include "Ray.hpp"

GL::Ray::Ray(const Vector<double>& point1, const Vector<double>& point2)
{
    _point1 = point1;
    _point2 = point2;
    _lab = _point2 - _point1;
}

Vector<double> GL::Ray::GetPoint1() const
{
    return _point1;
}

Vector<double> GL::Ray::GetPoint2() const
{
    return _point2;
}
