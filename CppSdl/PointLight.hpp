#pragma once

#include "LightBase.hpp"

namespace GL
{
	class PointLight : public LightBase
	{
	public:
		PointLight();
		PointLight(VD color, VD location) : LightBase(color, location, 1.0) {}
		PointLight(VD color, VD location, double intensity) : LightBase(color, location, intensity) {}

		virtual ~PointLight() override;

		//function to compute illumination
		//virtual bool ComputeIllumination(const VD& intPoint,
		//	const VD& localNormal,
		//	const pShapesVector& objectList, const pShape& currentObject,
		//	VD& color, double& intensity) override;

		virtual bool ComputeIllumination(const IntersectionInfo& intersectionInfo,
			const pShapesVector& objectList, const pShape& currentObject, VD& color, double& intensity) const override;
	};

}

