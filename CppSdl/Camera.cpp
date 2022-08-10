#include "Camera.hpp"


GL::Camera::Camera()
{
	_projectionScreenDistance = 1.0;
	_projectionScreenHorizontalSize = 1.0;
	_projectionScreenAspectRatio = 1.0;

	//_cameraPosition = VD{ {0.0,-10.0,0.0} };
	//_lookAt = VDs::Zero; //VD{ {0.0,0.0,0.0} };
	//_upVector = VDs::Uz; // VD{ {0.0,0.0,1.0} };

	//UpdateCameraGeometry();
}

void GL::Camera::SetPosition(const VD& newPosition)
{
	_cameraPosition = newPosition;
}

void GL::Camera::SetLookAt(const VD& newLookAt)
{
	_lookAt = newLookAt;
}

void GL::Camera::SetUpVector(const VD& upVector)
{
	_upVector = upVector;
}

void GL::Camera::SetLength(double newLength)
{
	_projectionScreenDistance = newLength;
}

void GL::Camera::SetHorizontalSize(double newSize)
{
	_projectionScreenHorizontalSize = newSize;
}

void GL::Camera::SetAspectRatio(double newAspect)
{
	_projectionScreenAspectRatio = newAspect;
}

VD GL::Camera::GetPosition() const
{
	return _cameraPosition;
}

VD GL::Camera::GetLookAt() const
{
	return _lookAt;
}

VD GL::Camera::GetUp() const
{
	return _upVector;
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
	return _projectionScreenCenter;
}

double GL::Camera::GetLength() const
{
	return _projectionScreenDistance;
}

double GL::Camera::GetHorizontalSize() const
{
	return _projectionScreenHorizontalSize;
}

double GL::Camera::GetAspectRatio() const
{
	return _projectionScreenAspectRatio;
}

//bool GL::Camera::GenerateRay(float projectionScreenX, float projectionScreenY, GL::Ray& cameraRay)
//{
//	//compute the location of the screen piont in world coordinates
//	VD screenWorldCoordinate =
//		_screenCenter +
//		_u * projectionScreenX +
//		_v * projectionScreenY;
//
//	cameraRay.SetPoints(_position,screenWorldCoordinate);
//
//	////use this point along with the camera position to compute the ray
//	//return GL::Ray(_position, screenWorldCoordinate);
//	return true;
//}
//
GL::Ray GL::Camera::GenerateRay(float projectionScreenX, float projectionScreenY) const
{
	//use this point along with the camera position to compute the ray
	return GL::Ray(
		_cameraPosition,
		_projectionScreenCenter + _u * projectionScreenX + _v * projectionScreenY //screenWorldCoordinate
	);
}

void GL::Camera::UpdateCameraGeometry()
{
	//first compute the vector from the camera position to the LookAt position
	_alignmentVector = !(_lookAt - _cameraPosition);

	//u, v, up correspond to x (horizontal), y (vertical)

	//compute the U and V vectors
	//_up is not normalized and is not vertical to the _aligmentVector
	_u = !(_alignmentVector ^ _upVector); //that's the horizontal vector towards right

	_v = _u ^ _alignmentVector; //VD::cross(_u, _alignmentVector)

	//we assume that the projection plane occurs at a distance of length on the aligmentVector direction
	//length should NOT be zero
	_projectionScreenCenter = _cameraPosition + _projectionScreenDistance * _alignmentVector;

	//modify the U and V vectors to match the size and aspect ratio!
	_u *= _projectionScreenHorizontalSize; //u length = width of the screen in world coordinates

	//aspect ratio = horizontal/vertical
	//v length = length of the screen in world coordinates
	_v *= _projectionScreenHorizontalSize / _projectionScreenAspectRatio;  

}
