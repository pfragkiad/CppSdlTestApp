#include "LightBase.hpp"

GL::LightBase::LightBase()
{
}

GL::LightBase::LightBase(VD color, VD location) :
	_lightColor(color), _intensity(1.0), _location(location)
{
}

GL::LightBase::LightBase(VD color, VD location, double intensity) :
	_lightColor(color), _intensity(intensity), _location(location)
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
