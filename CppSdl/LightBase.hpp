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
		LightBase(VD color,double intensity);
		LightBase(VD color,double intensity, VD location);
		virtual ~LightBase();

		//function to compute illumination contribution
		//virtual bool ComputeIllumination(const VD& intPoint, const VD& localNormal,
		//	const pShapesVector& objectList, const pShape& currentObject,
		//	VD& color, double& intensity);

		virtual bool ComputeIllumination(const IntersectionInfo& intersectionInfo,
			const pShapesVector& objectList, const pShape& currentObject, VD& color, double& intensity) const;


		VD _color{ VDs::Zero };
		VD _location{ VDs::Zero };
		double _intensity = 1.0;
	};


}

typedef std::shared_ptr<GL::LightBase> pLightBase;
typedef std::vector<pLightBase> pLightsVector;

