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

		virtual bool TestIntersection(const Ray& castRay, VectorD& intPoint, VectorD& localNormal, VectorD& localColor) override;

	private:

	};

}