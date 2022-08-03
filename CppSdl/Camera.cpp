#include "Camera.hpp"
#include "Ray.hpp"
#include <cmath>
#include "../Algebra/Algebra.h"

GL::Camera::Camera()
{
	_position = -10.0 * Vectors::UnitY; //Vector<double>{ {0.0,-10.0,0.0} };
	_lookAt = Vectors::Zero; //Vector<double>{ {0.0,0.0,0.0} };
	_up = Vectors::UnitZ; // Vector<double>{ {0.0,0.0,1.0} };

	_length = 1.0;
	_horizontalSize = 1.0;
	_aspectRatio = 1.0;

	UpdateCameraGeometry();
}

void GL::Camera::SetPosition(const Vector<double>& newPosition)
{
	_position = newPosition;
}

void GL::Camera::SetLookAt(const Vector<double>& newLookAt)
{
	_lookAt = newLookAt;
}

void GL::Camera::SetUp(const Vector<double>& upVector)
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

Vector<double> GL::Camera::GetPosition()
{
	return _position;
}

Vector<double> GL::Camera::GetLookAt()
{
	return _lookAt;
}

Vector<double> GL::Camera::GetUp()
{
	return _up;
}

Vector<double> GL::Camera::GetU()
{
	return _u;
}

Vector<double> GL::Camera::GetV()
{
	return _v;
}

Vector<double> GL::Camera::GetScreenCenter()
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
	Vector<double> screenWorldCoordinate =
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
	//_u = Vector<double>::cross(_alignmentVector, _up);
	_u = _alignmentVector ^ _up;
	_u.Normalize();
	_v = _u ^ _alignmentVector; //Vector<double>::cross(_u, _alignmentVector)
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
