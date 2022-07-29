#ifndef RAY_H
#define RAY_H
#include "../AlgebraTests/Vector.h"

namespace GL
{
	class Ray
	{
	public:
		Ray(const Vector<double>& point1, const Vector<double>& point2);

		Vector<double> GetPoint1() const;
		Vector<double> GetPoint2() const;

		Vector<double> _point1;
		Vector<double> _point2;
		Vector<double> _lab;
	};
}

#endif

