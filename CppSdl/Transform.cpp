
#include "Transform.hpp"

GL::Transform::Transform()
{

}

GL::Transform::~Transform()
{
}

//construct from a pair of matrices
GL::Transform::Transform(const MatrixD& fwd, const MatrixD& bck)
{
	//verify that the inputs are 4x4
	if (fwd.RowsCount() != 4 || fwd.ColsCount() != 4 ||
		bck.RowsCount() != 4 || bck.ColsCount() != 4)
	{
		throw std::invalid_argument("Cannot construct form, inputs are not all 4x4.");
	}
	_fwdtfm = fwd;
	_bcktfm = bck;
}

void GL::Transform::SetTransform(const VectorD& translation, const VectorD& rotation, const VectorD& scale)
{
	//define a matrix for each component of the transform

	MatrixD translationMatrix = Algebra::GetTranslation(translation);
	MatrixD rotationMatrixX = Algebra::GetRotationX(rotation[0]);
	MatrixD rotationMatrixY = Algebra::GetRotationY(rotation[1]);
	MatrixD rotationMatrixZ = Algebra::GetRotationZ(rotation[2]);
	MatrixD scaleMatrix = Algebra::GetScale(scale);

	//combine to give the final forward transform matrix
	_fwdtfm = translationMatrix * scaleMatrix * rotationMatrixX * rotationMatrixY * rotationMatrixZ;

	//_bcktfm = _fwdtfm;
	//http://www.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche0053.html#:~:text=and%20translation%20matrix)-,Inverse%20matrix%20of%20transformation%20matrix%20(rotation%20and%20translation%20matrix),R%7Ct%5D%20transformation%20matrix.&text=The%20inverse%20of%20transformation%20matrix%20%5BR%7Ct%5D%20is%20%5B,%2D%20R%5ET%20t%5D.
	//_bcktfm.Inverse(); //faster should be by getting the matrices above!
	_bcktfm = Algebra::GetInverseTransformation(_fwdtfm);
}

MatrixD GL::Transform::GetForward()
{
	return _fwdtfm;
}

MatrixD GL::Transform::GetBackward()
{
	return _bcktfm;
}

GL::Ray GL::Transform::Apply(const Ray& inputRay, bool isForward)
{
	Ray outputRay;
	outputRay._point1 = Apply(inputRay._point1, isForward);
	outputRay._point2 = Apply(inputRay._point2, isForward);
	outputRay._lab = outputRay._point2 - outputRay._point1;

	return outputRay;
}

VectorD GL::Transform::Apply(const VectorD& inputVector, bool isForward)
{
	//convert inputVector to a 4-element vector
	VectorD tempVector{ inputVector[0],inputVector[1],inputVector[2],inputVector[3],1.0 };

	//create a vector for the result
	VectorD resultVector = (isForward ? _fwdtfm : _bcktfm) * tempVector;
	
	//reform the output as a 3-element vector (ignore the last 1!)
	return VectorD{ resultVector[0],resultVector[1],resultVector[2] };
}
GL::Transform GL::operator*(const Transform& lhs, const Transform& rhs)
{
	//form the product of the two forward transforms
	MatrixD fwdResult = lhs._fwdtfm * rhs._fwdtfm;

	//cimpute the backward transform as the inverse of the forward transform
	//MatrixD bckResult = fwdResult; bckResult.Inverse();
	MatrixD bckResult = Algebra::GetInverseTransformation(fwdResult);

	//form the final result
	return Transform(fwdResult, bckResult);

}

GL::Transform GL::Transform::operator=(const Transform& rhs)
{
	if (this != &rhs) {
		_fwdtfm = rhs._fwdtfm;
		_bcktfm = rhs._bcktfm;
	}
	return *this;
}
//
//void GL::Transform::PrintMatrix(bool isForward)
//{
//	Print(isForward ? _fwdtfm : _bcktfm);
//}
//
//void GL::Transform::PrintVector(const VectorD& vector)
//{
//	std::cout << vector <<std::endl;
//}
//
//void GL::Transform::Print(const MatrixD& matrix)
//{
//	matrix.Print(3); std::cout << endl;
//}

