#pragma once

#include "../Algebra/Algebra.h"

#include "Ray.hpp"

//transformations
namespace GL
{
	class Transform
	{
	public:
		Transform();
		~Transform();

		//construct from a pair of matrices
		Transform(const MD& fwd, const MD& bck);
		
		//useful for static images
		Transform(const VD& translation,
			const VD& rotation,
			const VD& scale) {
			Set(translation, rotation, scale);
		}

		//function to set translation, rotation and scale components
		void Set(
			const VD& translation,
			const VD& rotation,
			const VD& scale
		);

		//function to return the transform matrices
		MD GetForward();
		MD GetBackward();

		//function to apply the transform
		Ray Apply(const Ray& inputRay, bool isForward);

		VD Apply(const VD& inputVector, bool isForward);

		//overload operators
		friend Transform operator*(const Transform& lhs, const Transform& rhs);
		Transform operator=(const Transform& rhs);

		////function to print transform matrix to stdout
		//void PrintMatrix(bool isForward);

		////function to allow printing of vectors
		//static void PrintVector(const VD& vector);

	private:
		//void Print(const MD& matrix);

		MD _fwdtfm{ Algebra::I4 };
		MD _bcktfm{ Algebra::I4 };

	};


}

