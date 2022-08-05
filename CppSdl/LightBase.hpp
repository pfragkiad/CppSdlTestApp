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
		virtual bool ComputeIllumination(const VD& intPoint, const VD& localNormal,
			const pShapesVector& objectList, const pShape& currentObject,
			VD& color, double& intensity);

		VD _color{ VDs::Zero };
		VD _location{ VDs::Zero };
		double _intensity = 1.0;
	};


}

typedef std::shared_ptr<GL::LightBase> pLightBase;
typedef std::vector<pLightBase> pLightsVector;

