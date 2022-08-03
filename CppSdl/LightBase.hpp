#pragma once

#include <memory>
#include "../Algebra/Algebra.h"
#include "Ray.hpp"
#include "Shape.hpp"


namespace GL
{
	class LightBase
	{
	public:
		LightBase();
		virtual ~LightBase();

		//function to compute illumination contribution
		virtual bool ComputeIllumination(const VectorD& intPoint, const VectorD& localNormal,
			const pShapesVector& objectList, const pShape& currentObject,
			VectorD& color, double& intensity);

		VectorD _color{ 0.0,0.0,0.0 };
		VectorD _location{ 0.0,0.0,0.0 };
		double _intensity = 1.0;
	};


}

typedef std::vector<std::shared_ptr<GL::LightBase>> pLightsVector;

