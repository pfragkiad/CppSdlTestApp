#include "Camera.hpp"


GL::Camera::Camera()
{
	_position = -10.0 * Algebra::Uy; //VectorD{ {0.0,-10.0,0.0} };
	_lookAt = Algebra::Zero; //VectorD{ {0.0,0.0,0.0} };
	_up = Algebra::Uz; // VectorD{ {0.0,0.0,1.0} };

	_length = 1.0;
	_horizontalSize = 1.0;
	_aspectRatio = 1.0;

	UpdateCameraGeometry();
}

void GL::Camera::SetPosition(const VectorD& newPosition)
{
	_position = newPosition;
}

void GL::Camera::SetLookAt(const VectorD& newLookAt)
{
	_lookAt = newLookAt;
}

void GL::Camera::SetUp(const VectorD& upVector)
{
	_up = upVector;
}

void GL::Camera::SetLength(double newLength)
{
	_length = newLength;
}

void GL::Camera::SetHorizontalSize(double newSize)
{
	_horizontalSize = newSize;
}

void GL::Camera::SetAspectRatio(double newAspect)
{
	_aspectRatio = newAspect;
}

VectorD GL::Camera::GetPosition()
{
	return _position;
}

VectorD GL::Camera::GetLookAt()
{
	return _lookAt;
}

VectorD GL::Camera::GetUp()
{
	return _up;
}

VectorD GL::Camera::GetU()
{
	return _u;
}

VectorD GL::Camera::GetV()
{
	return _v;
}

VectorD GL::Camera::GetScreenCenter()
{
	return _screenCenter;
}

double GL::Camera::GetLength()
{
	return _length;
}

double GL::Camera::GetHorizontalSize()
{
	return _horizontalSize;
}

double GL::Camera::GetAspectRatio()
{
	return _aspectRatio;
}

bool GL::Camera::GenerateRay(float projectionScreenX, float projectionScreenY, GL::Ray &cameraRay)
{
	//compute the location of the screen piont in world coordinates
	VectorD screenWorldCoordinate =
		_screenCenter +
		_u * projectionScreenX +
		_v * projectionScreenY;

	cameraRay._point1 = _position;
	cameraRay._point2 = screenWorldCoordinate;
	cameraRay._lab = screenWorldCoordinate - _position;

	////use this point along with the camera position to compute the ray
	//return GL::Ray(_position, screenWorldCoordinate);
	return true;
}

void GL::Camera::UpdateCameraGeometry()
{
	//first compute the vector from the camera position to the LookAt position
	_alignmentVector = _lookAt - _position;
	_alignmentVector.Normalize();

	//u, v, up correspond to x (horizontal), y (in-screen), z(up-vertical)

	//compute the U and V vectors
	//_up is not normalized and is not vertical to the _aligmentVector
	//_u = VectorD::cross(_alignmentVector, _up);
	_u = _alignmentVector ^ _up;
	_u.Normalize();
	_v = _u ^ _alignmentVector; //VectorD::cross(_u, _alignmentVector)
	//_v.Normalize();
	//_v = _up.Normalized(); //this should be if the _up is vertical to the alignment
	_screenCenter = _position + _length * _alignmentVector;

	//modify the U and V vectors to match the size and aspect ratio!
	//_u = _u * _horizontalSize;
	_u *= _horizontalSize;
	//aspect ratio = horizontal/vertical
	//_v = _v * (_horizontalSize / _aspectRatio);
	_v *= _horizontalSize / _aspectRatio;

}
