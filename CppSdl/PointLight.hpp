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
		virtual bool ComputeIllumination(const Vector<double>& intPoint,
			const Vector<double>& localNormal,
			const pShapesVector& objectList, const pShape& currentObject,
			Vector<double>& color, double& intensity) override;
	};

}

