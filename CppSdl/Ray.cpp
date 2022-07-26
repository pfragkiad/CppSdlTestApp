#include "Ray.hpp"

inline GL::Ray::Ray() //allowed since C++11
    : Ray(VDs::Zero, VDs::Uz)
{
    //_point1 = VD{0.0,0.0,0.0};
    //_point2 = VD{0.0,0.0,1.0};
    //_lab = _point2 - _point1;
}

GL::Ray::Ray(const VD& point1, const VD& point2)
    : _point1(point1), _point2(point2), _lab(point2-point1)
{
    //SetPoints(point1, point2);
}

//void GL::Ray::SetPoints(const VD point1, const VD point2)
//{
//    _point1 = point1;
//    _point2 = point2;
//    _lab = _point2 - _point1;
//
//}

VD GL::Ray::GetPoint1() const
{
    return _point1;
}

VD GL::Ray::GetPoint2() const
{
    return _point2;
}

VD GL::Ray::GetLab() const
{
    return _lab;
}
