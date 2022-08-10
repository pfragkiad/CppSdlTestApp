#pragma once

#include "Vector.h"
#include "Matrix.h"

typedef Vector<double> VD;
typedef Matrix<double> MD;

class VDs //static double 3d vectors
{
public:
	inline static const VD Zero{ 0.0,0.0,0.0 };
	inline static const VD One{ 1.0,1.0,1.0 };

	//Unit X double vector in 3D.
	inline static const VD Ux{ 1.0,0.0,0.0 };
	//Unit Y double vector in 3D.
	inline static const VD Uy{ 0.0,1.0,0.0 };
	//Unit Y double vector in 3D.
	inline static const VD Uz{ 0.0,0.0,1.0 };

	//Homogeneous coordinates with 4 dimensions represent points.
	inline static const VD ToHomogeneous(const VD v) //tested
	{
		return VD({ v[0],v[1],v[2],1.0 });
	}

	//Returns the first three coordinates (omits the last element).
	inline static const VD FromHomogeneous(const VD p) //tested
	{
		return VD({ p[0],p[1],p[2] });
	}
};


//Common statics
class MDs
{
public:
	inline static const MD I3{ 3,3,std::vector<double>{
		1.0,0.0,0.0,
		0.0,1.0,0.0,
		0.0,0.0,1.0
	} };

	inline static const MD I4{ 4,4,std::vector<double>{
		1.0,0.0,0.0,0.0,
		0.0,1.0,0.0,0.0,
		0.0,0.0,1.0,0.0,
		0.0,0.0,0.0,1.0
	} };

	//Transform a vector. If it is homogeneous then the homogeneous vector is returned. If it is not the non-homogeneous is returned.
	inline static VD TransformVD(const MD m, const VD v, bool returnHomogeneous)
	{
		bool isHomogeneous = v.Count() == 4u;
		if (isHomogeneous && v[3] != 1.0) 
			throw std::invalid_argument("Homogeneous vector last element should be 1.0");

		VD vh = isHomogeneous ? v : VDs::ToHomogeneous(v);
		VD rotVh = m * vh;
		if (returnHomogeneous) return rotVh;
		return VDs::FromHomogeneous(rotVh);
	}


	inline static MD GetTranslation(const VD& translation) //tested
	{
		//https://www.brainvoyager.com/bv/doc/UsersGuide/CoordsAndTransforms/SpatialTransformationMatrices.html#:~:text=The%204%20by%204%20transformation,in%20the%20first%20three%20columns.
		MD translationMatrix{ I4 };
		translationMatrix.Set(0, 3, translation[0]);
		translationMatrix.Set(1, 3, translation[1]);
		translationMatrix.Set(2, 3, translation[2]);
		return translationMatrix;
	}

	inline static  MD GetScale(const VD& scale) //tested
	{
		MD scaleMatrix{ I4 };
		scaleMatrix.Set(0, 0, scale[0]);
		scaleMatrix.Set(1, 1, scale[1]);
		scaleMatrix.Set(2, 2, scale[2]);
		return scaleMatrix;
	}

	//Rotate around X axis (CCW)
	//(1,1,0) -> (1,0,1)
	inline static MD GetRotationX(double angleX)
	{
		//https://www3.nd.edu/~pbui/teaching/cse.40166.fa10/slides/Lecture_4_Transformations_and_Matrices.pdf
		MD rotationMatrixX{ I4 };
		rotationMatrixX.Set(1, 1, cos(angleX));
		rotationMatrixX.Set(1, 2, -sin(angleX)); //TESTED
		rotationMatrixX.Set(2, 1, sin(angleX)); //TESTED
		rotationMatrixX.Set(2, 2, cos(angleX));
		return rotationMatrixX;
	}

	//Rotate around Y axis (CCW)
	inline static  MD GetRotationY(double angleY)
	{
		//based on: 
		//https://www.brainvoyager.com/bv/doc/UsersGuide/CoordsAndTransforms/SpatialTransformationMatrices.html#:~:text=The%204%20by%204%20transformation,in%20the%20first%20three%20columns.
		//https://www3.nd.edu/~pbui/teaching/cse.40166.fa10/slides/Lecture_4_Transformations_and_Matrices.pdf
		MD rotationMatrixY{ I4 };
		rotationMatrixY.Set(0, 0, cos(angleY));
		rotationMatrixY.Set(0, 2, sin(angleY)); //TESTED
		rotationMatrixY.Set(2, 0, -sin(angleY)); //TESTED
		rotationMatrixY.Set(2, 2, cos(angleY));
		return rotationMatrixY;
	}

	//Rotate around Z axis (CCW)
	inline static  MD GetRotationZ(double angleZ)
	{
		//based on: 
		//https://www.brainvoyager.com/bv/doc/UsersGuide/CoordsAndTransforms/SpatialTransformationMatrices.html#:~:text=The%204%20by%204%20transformation,in%20the%20first%20three%20columns.
		//https://www3.nd.edu/~pbui/teaching/cse.40166.fa10/slides/Lecture_4_Transformations_and_Matrices.pdf
		MD rotationMatrixZ{ I4 };
		rotationMatrixZ.Set(0, 0, cos(angleZ));
		rotationMatrixZ.Set(0, 1, -sin(angleZ)); //TESTED
		rotationMatrixZ.Set(1, 0, sin(angleZ)); //TESTED
		rotationMatrixZ.Set(1, 1, cos(angleZ));
		return rotationMatrixZ;
	}


	//Returns the inverse of a transformation matrix
	inline static MD GetInverseTransformation(MD m)
	{
		//	//http://www.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche0053.html#:~:text=and%20translation%20matrix)-,Inverse%20matrix%20of%20transformation%20matrix%20(rotation%20and%20translation%20matrix),R%7Ct%5D%20transformation%20matrix.&text=The%20inverse%20of%20transformation%20matrix%20%5BR%7Ct%5D%20is%20%5B,%2D%20R%5ET%20t%5D.
		MD RT = m.FindSubMatrix(3, 3).Transpose();
		VD t{ m.Get(0,3),m.Get(1,3),m.Get(2,3) };
		VD RTt = (-1.0) * RT * t;

		MD out{ I4 };
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				out.Set(i, j, RT.Get(i, j));

			out.Set(i, 3, RTt[i]);
		}
		return out;
	}

};


class Scalars
{
public:
	static inline constexpr double PI = 3.14159265358979323846;
	static inline constexpr double PI_2 = PI/2.0;
	static inline constexpr double PI_4 = PI / 4.0;
	static inline constexpr double TO_RADS = PI / 180.0;
	static inline constexpr double TO_DEGREES = 180.0 / PI;

//#define M_E        2.71828182845904523536   // e
//#define M_LOG2E    1.44269504088896340736   // log2(e)
//#define M_LOG10E   0.434294481903251827651  // log10(e)
//#define M_LN2      0.693147180559945309417  // ln(2)
//#define M_LN10     2.30258509299404568402   // ln(10)
//#define M_PI       3.14159265358979323846   // pi
//#define M_PI_2     1.57079632679489661923   // pi/2
//#define M_PI_4     0.785398163397448309616  // pi/4
//#define M_1_PI     0.318309886183790671538  // 1/pi
//#define M_2_PI     0.636619772367581343076  // 2/pi
//#define M_2_SQRTPI 1.12837916709551257390   // 2/sqrt(pi)
//#define M_SQRT2    1.41421356237309504880   // sqrt(2)
//#define M_SQRT1_2  0.707106781186547524401  // 1/sqrt(2)
};
