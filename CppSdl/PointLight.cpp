#include "PointLight.hpp"

#include <SDL.h> //M_PI
#include <iostream>

GL::PointLight::PointLight() :
	LightBase(/*lightColor*/ VD({ 255.0, 255.0, 255.0 }), /*location*/ VDs::Zero, /*intensity*/ 1.0)
{
}

GL::PointLight::~PointLight()
{
}

//bool GL::PointLight::ComputeIllumination(
//	const VD& intPoint, const VD& localNormal,
//	const pShapesVector& objectList, const pShape& currentObject,
//	VD& color, double& intensity)
bool GL::PointLight::ComputeIllumination(
	const GL::IntersectionInfo& intersectionInfo,
	const pShapesVector& objectList, const pShape& currentObject,
	VD& color, double& intensity) const
{
	//construct the vector pointing from the intersection point to the light
	//VD lightDir = !(_location - intPoint);
	VD lightDirection = !(intersectionInfo.Point - _location); //end-start

	//std::cout << intersectionInfo.Normal.LengthSquared() << ", " << lightDirection.LengthSquared() << std::endl;

	//compute a starting point (not useful yet)
	//VD startPoint = intPoint;
	//VD startPoint = intersectionInfo.Point;

	//compute the angle between the local normal and the light ray
	//assume that localNormal is a unit vector
	//double angle = acos(localNormal * lightDirection); //should be M_PI-...
	double angle = M_PI - acos(intersectionInfo.Normal * lightDirection); //should be M_PI-...


	//if the normal is pointing away from the light then we have no illumination
	//_USE_MATH_DEFINES must be defined, however M_PI conflicts with SDL declaration in SDL.h of M_PI
	constexpr double PI_2 = M_PI / 2.0; //1.57079632679489661923132169163975144;
	if (angle > PI_2)
	{
		color = _lightColor; //we export the light color and intensity
		intensity = 0.0;
		return false;
	}

	//we do have illumination
	//we export the light color and intensity
	color = _lightColor;
	intensity = _intensity * (1.0 - angle / PI_2);

	//intensity = _intensity * angle / M_PI_2;
	return true;

}
