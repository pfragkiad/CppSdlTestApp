#pragma once

#include "Shape.hpp"

namespace GL
{
	class Sphere :
		public Shape
	{
	public:
		Sphere();
		Sphere(double radius);
		Sphere(double radius , VD baseColor) :Shape(baseColor), _radius(radius) {}
		Sphere(double radius, VD baseColor, VD translation) :
			Shape(baseColor, Transform(MDs::GetTranslation(translation), MDs::GetTranslation(-translation))), _radius(radius) {}

		Sphere(double radius, VD baseColor, Transform transformMatrix)
			: Shape(baseColor, transformMatrix) , _radius(radius) {}

		Sphere(VD baseColor, Transform transformMatrix)
			: Shape(baseColor, transformMatrix) ,_radius(1.0) {}

		virtual ~Sphere() override;

		void SetRadius(double radius);
		double GetRadius() const;

		//virtual bool TestIntersection(const Ray& castRay, VD& intersectionPoint, VD& localNormal, VD& localColor) override;
		virtual IntersectionInfo TestIntersection(const Ray& castRay) const override;

	private:
		double _radius;

	};

}