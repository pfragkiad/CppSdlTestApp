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
		void SetPosition(const VectorD& newPosition);
		void SetLookAt(const VectorD& newLookAt);
		void SetUp(const VectorD& upVector);

		//distange of the projection screen from the pinhole
		void SetLength(double newLength);
		void SetHorizontalSize(double newSize);
		void SetAspectRatio(double newAspect);

		//functions to return camera parameters
		VectorD GetPosition();
		VectorD GetLookAt();
		VectorD GetUp();
		VectorD GetU(); //projectionScreenU
		VectorD GetV(); //projectionScreenV
		VectorD GetScreenCenter(); //projectionScreenCenter
		double GetLength();
		double GetHorizontalSize();
		double GetAspectRatio();

		//function to generate a ray
		//projectionScreenX/Y [-1.0f to 1.0f]
		bool GenerateRay(float projectionScreenX, float projectionScreenY, Ray& cameraRay);


		void UpdateCameraGeometry();

	private:
		VectorD _position;
		VectorD _lookAt;
		VectorD _up;
		double _length;
		double _horizontalSize;
		double _aspectRatio;

		VectorD _alignmentVector;
		//projection screen parameters (U, V, center)
		VectorD _u;
		VectorD _v;
		VectorD _screenCenter;

	};


}
#endif

