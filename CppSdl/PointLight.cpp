#include "PointLight.hpp"

GL::PointLight::PointLight()
{
    _color = Vector({ 1.0, 1.0, 1.0 });
    _intensity = 1.0;
}

GL::PointLight::~PointLight()
{
}

bool GL::PointLight::ComputeIllumination(const Vector<double>& intPoint, const Vector<double>& localNormal, const pShapesVector& objectList, const pShape& currentObject, Vector<double>& color, double& intensity)
{
    //construct the vector pointing from the intersection point to the light
    Vector<double> lightDir = !(_location - intPoint);

    //compute a starting point (not useful yet)
    Vector<double> startPoint = intPoint;

    //compute the angle between the local normal and the light ray
    //assume that localNormal is a unit vector
    double angle = acos(localNormal * lightDir);

    //if the normal is pointing away from the light then we have no illumination
    //_USE_MATH_DEFINES must be defined
    if(angle > M_PI/2 )

    return false;
}
