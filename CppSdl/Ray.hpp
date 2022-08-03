#ifndef RAY_H
#define RAY_H
#include "../Algebra/Algebra.h"

namespace GL
{
	class Ray
	{
	public:
		Ray();
		Ray(const VectorD& point1, const VectorD& point2);

		VectorD GetPoint1() const;
		VectorD GetPoint2() const;

		VectorD _point1;
		VectorD _point2;
		VectorD _lab;
	};
}

#endif

