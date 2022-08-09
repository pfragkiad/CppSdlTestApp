#include "LightBase.hpp"

GL::LightBase::LightBase()
{
}

GL::LightBase::LightBase(VD color, double intensity):
    _color(color), _intensity(intensity)
{
}

GL::LightBase::LightBase(VD color,double intensity, VD location):
    _color(color),_intensity(intensity), _location(location)
{
}

GL::LightBase::~LightBase()
{
}

bool GL::LightBase::ComputeIllumination(
    const IntersectionInfo& intersectionInfo, const pShapesVector& objectList, const pShape& currentObject,
    VD& color, double& intensity) const
{
    return false;
}

//bool GL::LightBase::ComputeIllumination(
//    const VD& intPoint,
//    const VD& localNormal, 
//    const pShapesVector& objectList, 
//    const pShape& currentObject,
//    VD& color,
//    double& intensity)
//{
//    return false;
//}
