#pragma once

#include <memory>
#include "../Algebra/Vector.h"
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
		virtual bool ComputeIllumination(const Vector<double>& intPoint, const Vector<double>& localNormal,
			const pShapesVector& objectList, const pShape& currentObject,
			Vector<double>& color, double& intensity);

		Vector<double> _color{ 0.0,0.0,0.0 };
		Vector<double> _location{ 0.0,0.0,0.0 };
		double _intensity = 1.0;
	};


}

