#include "LightBase.hpp"

GL::LightBase::LightBase()
{
}

GL::LightBase::~LightBase()
{
}

bool GL::LightBase::ComputeIllumination(const VectorD& intPoint,
    const VectorD& localNormal, 
    const pShapesVector& objectList,   const pShape& currentObject,
    VectorD& color, double& intensity)
{
    return false;
}
