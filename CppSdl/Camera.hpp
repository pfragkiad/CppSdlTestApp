#ifndef CAMERA_H
#define CAMERA_H

#include "../Algebra/Algebra.h"
#include "Ray.hpp"


namespace GL
{
	class Camera
	{
	public:
		Camera();

		//function to set camera parameters
		void SetPosition(const VD& newPosition);
		void SetLookAt(const VD& newLookAt);
		void SetUp(const VD& upVector);

		//distange of the projection screen from the pinhole
		void SetLength(double newLength);
		void SetHorizontalSize(double newSize);
		void SetAspectRatio(double newAspect);

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
		bool GenerateRay(float projectionScreenX, float projectionScreenY, Ray& cameraRay);


		void UpdateCameraGeometry();

	private:
		VD _position;
		VD _lookAt;
		VD _up;
		double _length;
		double _horizontalSize;
		double _aspectRatio;

		VD _alignmentVector;
		//projection screen parameters (U, V, center)
		VD _u;
		VD _v;
		VD _screenCenter;

	};


}
#endif

