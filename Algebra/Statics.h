#pragma once

#include "Vector.h"
#include "Matrix.h"

typedef Vector<double> VD;
typedef Matrix<double> MD;

//Common statics
namespace Algebra
{
	//Returns a Zero 3D Vector<double>.
	const VD Zero{ 0.0,0.0,0.0 };
	const VD Ux{ 1.0,0.0,0.0 };
	const VD Uy{ 0.0,1.0,0.0 };
	const VD Uz{ 0.0,0.0,1.0 };


	const MD I3{ 3,3,std::vector<double>{
		1.0,0.0,0.0,
		0.0,1.0,0.0,
		0.0,0.0,1.0
	} };

	const MD I4{ 4,4,std::vector<double>{
		1.0,0.0,0.0,0.0,
		0.0,1.0,0.0,0.0,
		0.0,0.0,1.0,0.0,
		0.0,0.0,0.0,1.0
	} };

	inline MD GetTranslation(VD translation)
	{
		MD translationMatrix{ I4 };
		translationMatrix.Set(0, 3, translation[0]);
		translationMatrix.Set(1, 3, translation[1]);
		translationMatrix.Set(2, 3, translation[2]);
		return translationMatrix;
	}

	inline MD GetRotationZ(double angleZ)
	{
		MD rotationMatrixZ{ I4 };
		rotationMatrixZ.Set(0, 0, cos(angleZ));
		rotationMatrixZ.Set(0, 1, -sin(angleZ));
		rotationMatrixZ.Set(1, 0, sin(angleZ));
		rotationMatrixZ.Set(1, 1, cos(angleZ));
		return rotationMatrixZ;
	}

	inline MD GetRotationX(double angleX)
	{
		MD rotationMatrixX{ I4 };
		rotationMatrixX.Set(1, 1, cos(angleX));
		rotationMatrixX.Set(1, 2, -sin(angleX));
		rotationMatrixX.Set(2, 1, sin(angleX));
		rotationMatrixX.Set(2, 2, cos(angleX));
		return rotationMatrixX;
	}

	inline MD GetRotationY(double angleY)
	{
		MD rotationMatrixY{ I4 };
		rotationMatrixY.Set(0, 0, cos(angleY));
		rotationMatrixY.Set(0, 2, -sin(angleY));
		rotationMatrixY.Set(2, 0, sin(angleY));
		rotationMatrixY.Set(2, 2, cos(angleY));
		return rotationMatrixY;
	}

	inline MD GetScale(VD scale)
	{
		MD scaleMatrix{ I4 };
		scaleMatrix.Set(0, 0, scale[0]);
		scaleMatrix.Set(1, 1, scale[1]);
		scaleMatrix.Set(2, 2, scale[2]);
		return scaleMatrix;
	}

	//Returns the inverse of a transformation matrix
	inline MD GetInverseTransformation(MD m)
	{
		//	//http://www.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche0053.html#:~:text=and%20translation%20matrix)-,Inverse%20matrix%20of%20transformation%20matrix%20(rotation%20and%20translation%20matrix),R%7Ct%5D%20transformation%20matrix.&text=The%20inverse%20of%20transformation%20matrix%20%5BR%7Ct%5D%20is%20%5B,%2D%20R%5ET%20t%5D.
		MD RT = m.FindSubMatrix(3, 3).Transpose();
		VD t{ m.Get(0,3),m.Get(1,3),m.Get(2,3) };
		VD RTt = (-1.0)*RT * t;
	
		MD out{ I4};
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				out.Set(i, j, RT.Get(i, j));

			out.Set(i, 3, RTt[i]);
		}
		return out;
	}

	};

