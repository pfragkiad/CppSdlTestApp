#pragma once

#include "LightBase.hpp"

namespace GL
{
	class PointLight : public LightBase
	{
	public:
		PointLight();
		virtual ~PointLight() override;

		//function to compute illumination
		virtual bool ComputeIllumination(const VD& intPoint,
			const VD& localNormal,
			const pShapesVector& objectList, const pShape& currentObject,
			VD& color, double& intensity) override;
	};

}

