#pragma once

#include "Shape.hpp"

namespace GL
{
	class Sphere :
		public Shape
	{
	public:
		Sphere();

		virtual ~Sphere() override;

		virtual bool TestIntersection(const Ray& castRay, Vector<double>& intPoint, Vector<double>& localNormal, Vector<double>& localColor) override;

	private:

	};

}