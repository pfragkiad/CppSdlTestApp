#include "LightBase.hpp"

GL::LightBase::LightBase()
{
}

GL::LightBase::~LightBase()
{
}

bool GL::LightBase::ComputeIllumination(const VD& intPoint,
    const VD& localNormal, 
    const pShapesVector& objectList,   const pShape& currentObject,
    VD& color, double& intensity)
{
    return false;
}
