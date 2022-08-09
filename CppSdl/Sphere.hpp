#pragma once

#include "Shape.hpp"

namespace GL
{
	class Sphere :
		public Shape
	{
	public:
		Sphere();
		Sphere(VD baseColor, Transform transformMatrix)
			: Shape(baseColor, transformMatrix) {}

		virtual ~Sphere() override;

		//virtual bool TestIntersection(const Ray& castRay, VD& intersectionPoint, VD& localNormal, VD& localColor) override;
		virtual IntersectionInfo TestIntersection(const Ray& castRay) const override;
	private:

	};

}