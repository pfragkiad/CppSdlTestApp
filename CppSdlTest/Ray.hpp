#ifndef RAY_H
#define RAY_H
#include "algebra/Vector.h"

namespace GL
{
	class Ray
	{
	public:
		Ray(const Vector<double>& point1, const Vector<double>& point2);

		Vector<double> GetPoint1() const;
		Vector<double> GetPoint2() const;

		Vector<double> _point1 = Vector<double>(3);
		Vector<double> _point2 = Vector<double>(3);
		Vector<double> _lab = Vector<double>(3);
	};
}

#endif

