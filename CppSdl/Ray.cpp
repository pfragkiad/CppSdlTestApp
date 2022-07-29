#include "Ray.hpp"

GL::Ray::Ray() //allowed since C++1
    : Ray(Vector<double>{0.0, 0.0, 0.0}, Vector<double>{0.0, 0.0, 1.0})
{
    //_point1 = Vector<double>{0.0,0.0,0.0};
    //_point2 = Vector<double>{0.0,0.0,1.0};
    //_lab = _point2 - _point1;
}

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
