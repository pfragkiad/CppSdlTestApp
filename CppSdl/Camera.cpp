#include "Camera.hpp"


GL::Camera::Camera()
{
	_position = VD{ {0.0,-10.0,0.0} };
	_lookAt = VDs::Zero; //VD{ {0.0,0.0,0.0} };
	_up = VDs::Uz; // VD{ {0.0,0.0,1.0} };

	_length = 1.0;
	_horizontalSize = 1.0;
	_aspectRatio = 1.0;

	UpdateCameraGeometry();
}

void GL::Camera::SetPosition(const VD& newPosition)
{
	_position = newPosition;
}

void GL::Camera::SetLookAt(const VD& newLookAt)
{
	_lookAt = newLookAt;
}

void GL::Camera::SetUp(const VD& upVector)
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

VD GL::Camera::GetPosition() const
{
	return _position;
}

VD GL::Camera::GetLookAt() const
{
	return _lookAt;
}

VD GL::Camera::GetUp() const
{
	return _up;
}

VD GL::Camera::GetU() const
{
	return _u;
}

VD GL::Camera::GetV() const
{
	return _v;
}

VD GL::Camera::GetScreenCenter() const
{
	return _screenCenter;
}

double GL::Camera::GetLength() const
{
	return _length;
}

double GL::Camera::GetHorizontalSize() const
{
	return _horizontalSize;
}

double GL::Camera::GetAspectRatio() const
{ 
	return _aspectRatio;
}

bool GL::Camera::GenerateRay(float projectionScreenX, float projectionScreenY, GL::Ray& cameraRay)
{
	//compute the location of the screen piont in world coordinates
	VD screenWorldCoordinate =
		_screenCenter +
		_u * projectionScreenX +
		_v * projectionScreenY;

	cameraRay.SetPoints(_position,screenWorldCoordinate);

	////use this point along with the camera position to compute the ray
	//return GL::Ray(_position, screenWorldCoordinate);
	return true;
}

void GL::Camera::UpdateCameraGeometry()
{
	//first compute the vector from the camera position to the LookAt position
	_alignmentVector = !(_lookAt - _position);
	//_alignmentVector.Normalize();

	//u, v, up correspond to x (horizontal), y (in-screen), z(up-vertical)

	//compute the U and V vectors
	//_up is not normalized and is not vertical to the _aligmentVector
	//_u = VD::cross(_alignmentVector, _up);
	_u = !(_alignmentVector ^ _up);
	//_u.Normalize();
	_v = _u ^ _alignmentVector; //VD::cross(_u, _alignmentVector)
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
