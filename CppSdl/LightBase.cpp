#include "LightBase.hpp"

GL::LightBase::LightBase()
{
}

GL::LightBase::~LightBase()
{
}

bool GL::LightBase::ComputeIllumination(const Vector<double>& intPoint,
    const Vector<double>& localNormal, 
    const pShapesVector& objectList,   const pShape& currentObject,
    Vector<double>& color, double& intensity)
{
    return false;
}
