
#include "Transform.hpp"

#include <tuple>

GL::Transform::Transform()
{

}

GL::Transform::~Transform()
{
}

//construct from a pair of matrices
GL::Transform::Transform(const MD& fwd, const MD& bck)
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

void GL::Transform::Set(const VD& translation, const VD& rotation, const VD& scale)
{
	//define a matrix for each component of the transform
	tuple<VD,VD,VD> par(translation, rotation, scale);

	MD translationMatrix = MDs::GetTranslation(translation);
	MD rotationMatrixX = MDs::GetRotationX(rotation[0]);
	MD rotationMatrixY = MDs::GetRotationY(rotation[1]);
	MD rotationMatrixZ = MDs::GetRotationZ(rotation[2]);
	MD scaleMatrix = MDs::GetScale(scale);

	//combine to give the final forward transform matrix

	//SRT (scale rotate translate)
	//https://docs.microsoft.com/en-us/dotnet/desktop/winforms/advanced/why-transformation-order-is-significant?view=netframeworkdesktop-4.8
	_fwdtfm = translationMatrix * scaleMatrix * rotationMatrixX * rotationMatrixY * rotationMatrixZ;
	//_fwdtfm = translationMatrix  * rotationMatrixX * rotationMatrixY * rotationMatrixZ* scaleMatrix;

	//_bcktfm = Algebra::GetScale(1.0/scale)
	//	* Algebra::GetRotationZ(rotation[2])
	//	* Algebra::GetRotationY(-rotation[1]) 
	//	* Algebra::GetRotationX(-rotation[0])
	//	* Algebra::GetTranslation(-translation); //possibly correct
	_bcktfm = _fwdtfm; _bcktfm.Inverse();
	//http://www.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche0053.html#:~:text=and%20translation%20matrix)-,Inverse%20matrix%20of%20transformation%20matrix%20(rotation%20and%20translation%20matrix),R%7Ct%5D%20transformation%20matrix.&text=The%20inverse%20of%20transformation%20matrix%20%5BR%7Ct%5D%20is%20%5B,%2D%20R%5ET%20t%5D.
	// //faster should be by getting the matrices above!
	//_bcktfm = Algebra::GetInverseTransformation(_fwdtfm); //incorrect
}

MD GL::Transform::GetForward()
{
	return _fwdtfm;
}

MD GL::Transform::GetBackward()
{
	return _bcktfm;
}

GL::Ray GL::Transform::Apply(const Ray& inputRay, bool isForward)
{
	return Ray(Apply(inputRay.GetPoint1(), isForward), Apply(inputRay.GetPoint2(), isForward));
}

VD GL::Transform::Apply(const VD& inputVector, bool isForward)
{
	//convert inputVector to a 4-element vector
	//VD tempVector{ inputVector[0],inputVector[1],inputVector[2],1.0 };

	//create a vector for the result
	//VD resultVector = (isForward ? _fwdtfm : _bcktfm) * tempVector;
	
	//reform the output as a 3-element vector (ignore the last 1!)
	//return VD{ resultVector[0],resultVector[1],resultVector[2] };
	return VDs::FromHomogeneous((isForward ? _fwdtfm : _bcktfm) * VDs::ToHomogeneous(inputVector));
}
GL::Transform GL::operator*(const Transform& lhs, const Transform& rhs)
{
	//form the product of the two forward transforms
	MD fwdResult = lhs._fwdtfm * rhs._fwdtfm;

	//cimpute the backward transform as the inverse of the forward transform
	MD bckResult = fwdResult; bckResult.Inverse();
	//MD bckResult = Algebra::GetInverseTransformation(fwdResult);

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
//void GL::Transform::PrintVector(const VD& vector)
//{
//	std::cout << vector <<std::endl;
//}
//
//void GL::Transform::Print(const MD& matrix)
//{
//	matrix.Print(3); std::cout << endl;
//}

