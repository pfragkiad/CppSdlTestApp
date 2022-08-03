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
		virtual bool ComputeIllumination(const VectorD& intPoint,
			const VectorD& localNormal,
			const pShapesVector& objectList, const pShape& currentObject,
			VectorD& color, double& intensity) override;
	};

}

