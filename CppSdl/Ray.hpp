#ifndef RAY_H
#define RAY_H
#include "../Algebra/Algebra.h"

namespace GL
{
	class Ray
	{
	public:
		Ray();
		Ray(const VD& point1, const VD& point2);

		VD GetPoint1() const;
		VD GetPoint2() const;

		VD _point1;
		VD _point2;
		VD _lab;
	};
}

#endif

