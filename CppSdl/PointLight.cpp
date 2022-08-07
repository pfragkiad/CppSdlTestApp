#include "PointLight.hpp"

GL::PointLight::PointLight()
{
	_color = Vector({ 1.0, 1.0, 1.0 });
	_intensity = 1.0;
}

GL::PointLight::~PointLight()
{
}

bool GL::PointLight::ComputeIllumination(const VD& intPoint, const VD& localNormal,
	const pShapesVector& objectList, const pShape& currentObject,
	VD& color, double& intensity)
{
	//construct the vector pointing from the intersection point to the light
	VD lightDir = !(_location - intPoint);

	//compute a starting point (not useful yet)
	VD startPoint = intPoint;

	//compute the angle between the local normal and the light ray
	//assume that localNormal is a unit vector
	double angle = acos(localNormal * lightDir); //should be M_PI-...

	//if the normal is pointing away from the light then we have no illumination
	//_USE_MATH_DEFINES must be defined (M_PI conflicts with SDL declaration of M_PI)
	constexpr double PI_2 = 1.57079632679489661923132169163975144;
	if (angle > PI_2)
	{
		color = _color;
		intensity = 0.0;
		return false;
	}
	else
	{
		//we do have illumination
		color = _color;
		intensity = _intensity * (1.0 - angle / PI_2);
		//intensity = _intensity * angle / M_PI_2;
		return true;
	}

	return false;
}
