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
		Transform(const MatrixD& fwd, const MatrixD& bck);

		//function to set translation, rotation and scale components
		void SetTransform(
			const VectorD& translation,
			const VectorD& rotation,
			const VectorD& scale
		);

		//function to return the transform matrices
		MatrixD GetForward();
		MatrixD GetBackward();

		//function to apply the transform
		Ray Apply(const Ray& inputRay, bool isForward);

		VectorD Apply(const VectorD& inputVector, bool isForward);

		//overload operators
		friend Transform operator*(const Transform& lhs, const Transform& rhs);
		Transform operator=(const Transform& rhs);

		////function to print transform matrix to stdout
		//void PrintMatrix(bool isForward);

		////function to allow printing of vectors
		//static void PrintVector(const VectorD& vector);

	private:
		//void Print(const MatrixD& matrix);

		MatrixD _fwdtfm{ Algebra::I4 };
		MatrixD _bcktfm{ Algebra::I4 };

	};


}

