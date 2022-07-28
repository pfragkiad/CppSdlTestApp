#ifndef CAMERA_H
#define CAMERA_H

#include "./algebra/Vector.h"
#include "Ray.hpp"

namespace GL
{
	class Camera
	{
	public:
		Camera();

		//function to set camera parameters
		void SetPosition(const Vector<double>& newPosition);
		void SetLookAt(const Vector<double>& newLookAt);
		void SetUp(const Vector<double>& upVector);

		//distange of the projection screen from the pinhole
		void SetLength(double newLength);
		void SetHorizontalSize(double newSize);
		void SetAspectRatio(double newAspect);

		//functions to return camera parameters
		Vector<double> GetPosition();
		Vector<double> GetLookAt();
		Vector<double> GetUp();
		Vector<double> GetU(); //projectionScreenU
		Vector<double> GetV(); //projectionScreenV
		Vector<double> GetScreenCenter(); //projectionScreenCenter
		double GetLength();
		double GetHorizontalSize();
		double GetAspectRatio();

		//function to generate a ray
		//projectionScreenX/Y [-1.0f to 1.0f]
		Ray GenerateRay(float projectionScreenX, float projectionScreenY);


		void UpdateCameraGeometry();

	private:
		Vector<double> _position = Vector<double>(3);
		Vector<double> _lookAt = Vector<double>(3);
		Vector<double> _up = Vector<double>(3);
		double _length;
		double _horizontalSize;
		double _aspectRatio;

		Vector<double> _alignmentVector = Vector<double>(3);
		//projection screen parameters (U, V, center)
		Vector<double> _u = Vector<double>(3);
		Vector<double> _v = Vector<double>(3);
		Vector<double> _screenCenter = Vector<double>(3);

	};


}
#endif

