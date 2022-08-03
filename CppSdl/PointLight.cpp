#include "PointLight.hpp"

GL::PointLight::PointLight()
{
    _color = Vector({ 1.0, 1.0, 1.0 });
    _intensity = 1.0;
}

GL::PointLight::~PointLight()
{
}

bool GL::PointLight::ComputeIllumination(const VectorD& intPoint, const VectorD& localNormal, 
    const pShapesVector& objectList, const pShape& currentObject,
    VectorD& color, double& intensity)
{
    //construct the vector pointing from the intersection point to the light
    VectorD lightDir = !(_location - intPoint);

    //compute a starting point (not useful yet)
    VectorD startPoint = intPoint;

    //compute the angle between the local normal and the light ray
    //assume that localNormal is a unit vector
    double angle =  M_PI -  acos(localNormal * lightDir);

    //if the normal is pointing away from the light then we have no illumination
    //_USE_MATH_DEFINES must be defined
    if (angle > M_PI_2)
    {
        color = _color;
        intensity = 0.0;
        return false;
    }
    else
    {
        //we do have illumination
        color = _color;
        intensity = _intensity * (1.0 - angle / M_PI_2);
        //intensity = _intensity * angle / M_PI_2;
        return true;
    }

    return false;
}
