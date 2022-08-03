#pragma once

#include "Vector.h"
#include "Matrix.h"

typedef Vector<double> VectorD;
typedef Matrix<double> MatrixD;

//Common statics
namespace Algebra
{
	const VectorD Zero{ 0.0,0.0,0.0 };
	const VectorD Ux{ 1.0,0.0,0.0 };
	const VectorD Uy{ 0.0,1.0,0.0 };
	const VectorD Uz{ 0.0,0.0,1.0 };


	const MatrixD I3{ 3,3,std::vector<double>{
		1.0,0.0,0.0,
		0.0,1.0,0.0,
		0.0,0.0,1.0
	} };

	const MatrixD I4{ 4,4,std::vector<double>{
		1.0,0.0,0.0,0.0,
		0.0,1.0,0.0,0.0,
		0.0,0.0,1.0,0.0,
		0.0,0.0,0.0,1.0
	} };

	inline MatrixD GetTranslation(VectorD translation)
	{
		MatrixD translationMatrix{ I4 };
		translationMatrix.Set(0, 3, translation[0]);
		translationMatrix.Set(1, 3, translation[1]);
		translationMatrix.Set(2, 3, translation[2]);
		return translationMatrix;
	}

	inline MatrixD GetRotationZ(double angleZ)
	{
		MatrixD rotationMatrixZ{ I4 };
		rotationMatrixZ.Set(0, 0, cos(angleZ));
		rotationMatrixZ.Set(0, 1, -sin(angleZ));
		rotationMatrixZ.Set(1, 0, sin(angleZ));
		rotationMatrixZ.Set(1, 1, cos(angleZ));
		return rotationMatrixZ;
	}

	inline MatrixD GetRotationX(double angleX)
	{
		MatrixD rotationMatrixX{ I4 };
		rotationMatrixX.Set(1, 1, cos(angleX));
		rotationMatrixX.Set(1, 2, -sin(angleX));
		rotationMatrixX.Set(2, 1, sin(angleX));
		rotationMatrixX.Set(2, 2, cos(angleX));
		return rotationMatrixX;
	}

	inline MatrixD GetRotationY(double angleY)
	{
		MatrixD rotationMatrixY{ I4 };
		rotationMatrixY.Set(0, 0, cos(angleY));
		rotationMatrixY.Set(0, 2, -sin(angleY));
		rotationMatrixY.Set(2, 0, sin(angleY));
		rotationMatrixY.Set(2, 2, cos(angleY));
		return rotationMatrixY;
	}

	inline MatrixD GetScale(VectorD scale)
	{
		MatrixD scaleMatrix{ I4 };
		scaleMatrix.Set(0, 0, scale[0]);
		scaleMatrix.Set(1, 1, scale[1]);
		scaleMatrix.Set(2, 2, scale[2]);
		return scaleMatrix;
	}

	//Returns the inverse of a transformation matrix
	inline MatrixD GetInverseTransformation(MatrixD m)
	{
		//	//http://www.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche0053.html#:~:text=and%20translation%20matrix)-,Inverse%20matrix%20of%20transformation%20matrix%20(rotation%20and%20translation%20matrix),R%7Ct%5D%20transformation%20matrix.&text=The%20inverse%20of%20transformation%20matrix%20%5BR%7Ct%5D%20is%20%5B,%2D%20R%5ET%20t%5D.
		MatrixD RT = m.FindSubMatrix(3, 3).Transpose();
		VectorD t{ m.Get(0,3),m.Get(1,3),m.Get(2,3) };
		VectorD RTt = (-1.0)*RT * t;
	
		MatrixD out{ I4};
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				out.Set(i, j, RT.Get(i, j));

			out.Set(i, 3, RTt[i]);
		}
		return out;
	}

	};

