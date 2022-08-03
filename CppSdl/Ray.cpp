#include "Ray.hpp"

GL::Ray::Ray() //allowed since C++1
    : Ray(VectorD{0.0, 0.0, 0.0}, VectorD{0.0, 0.0, 1.0})
{
    //_point1 = VectorD{0.0,0.0,0.0};
    //_point2 = VectorD{0.0,0.0,1.0};
    //_lab = _point2 - _point1;
}

GL::Ray::Ray(const VectorD& point1, const VectorD& point2)
{
    _point1 = point1;
    _point2 = point2;
    _lab = _point2 - _point1;
}

VectorD GL::Ray::GetPoint1() const
{
    return _point1;
}

VectorD GL::Ray::GetPoint2() const
{
    return _point2;
}
