#ifndef RAY_H
#define RAY_H
#include "../Algebra/Algebra.h"

namespace GL
{
	class Ray
	{
		friend class Sphere; //friendship is not inherited (e.g. from Shape)
		friend class Transform;

	public:
		Ray();
		Ray(const VD& point1, const VD& point2);

		//void SetPoints(const VD point1, const VD point2);

		VD GetPoint1() const;
		VD GetPoint2() const;
		VD GetLab() const;

	private:
		VD _point1;
		VD _point2;
		VD _lab;
	};
}

#endif

