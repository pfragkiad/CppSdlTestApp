#pragma once

#include "../Algebra/Algebra.h"
#include "Ray.hpp"

namespace GL
{
	class Camera
	{
	public:
		Camera();

		//distange of the projection screen from the pinhole
		void SetLength(double newLength);
		void SetHorizontalSize(double newSize);
		void SetAspectRatio(double newAspect);

		//typically this should be done once prior to setting up the position of the camera
		inline void SetProjectionScreen(double cameraLength, double projectionScreenHorizontalSize, double projectionScreenAspectRatio)
		{
			_projectionScreenDistance = cameraLength;
			_projectionScreenHorizontalSize = projectionScreenHorizontalSize;
			_projectionScreenAspectRatio = projectionScreenAspectRatio;
		}

		//function to set camera parameters
		void SetPosition(const VD& newPosition);
		void SetLookAt(const VD& newLookAt);
		void SetUpVector(const VD& upVector);


		//Setting the camera, always updates the camera geometry.
		inline void SetCamera(VD cameraPosition, VD lookAt, VD upVector)
		{
			_cameraPosition = cameraPosition;
			_lookAt = lookAt; 
			_upVector = upVector;
			UpdateCameraGeometry();
		}

		//functions to return camera parameters
		VD GetPosition() const;
		VD GetLookAt() const;
		VD GetUp() const;
		VD GetU() const; //projectionScreenU
		VD GetV() const; //projectionScreenV
		VD GetScreenCenter() const; //projectionScreenCenter
		double GetLength() const;
		double GetHorizontalSize() const;
		double GetAspectRatio() const;

		//function to generate a ray
		//projectionScreenX/Y [-1.0f to 1.0f]
		//bool GenerateRay(float projectionScreenX, float projectionScreenY, Ray& cameraRay);
		Ray GenerateRay(float projectionScreenX, float projectionScreenY) const;


		void UpdateCameraGeometry();

	private:
		VD _cameraPosition;
		VD _lookAt;
		VD _upVector;

		double _projectionScreenDistance; //_cameraLength
		double _projectionScreenHorizontalSize;
		double _projectionScreenAspectRatio;

		VD _alignmentVector;
		//projection screen parameters (U, V, center)
		VD _u;
		VD _v;
		VD _projectionScreenCenter;

	};


}


