#include "../Algebra/Algebra.h"
#include "Window.hpp"

#include <iostream>

using namespace GL;

void testCamera()
{
	Camera testCamera;
	testCamera.SetPosition(Algebra::Zero);
	testCamera.SetLookAt(2.0*Algebra::Ux);
	testCamera.SetUp(Algebra::Uz);
	testCamera.SetLength(1.0);
	testCamera.SetHorizontalSize(1.0);
	testCamera.SetAspectRatio(1.0);
	testCamera.UpdateCameraGeometry();

	//get the screen center and U, V vectors and display
	VectorD screenCenter = testCamera.GetScreenCenter();
	VectorD screenU = testCamera.GetU();
	VectorD screenV = testCamera.GetV();
	std::cout
		<< "Center:\n" << screenCenter
		<< "\nU:\n" << screenU << "\nV:\n" << screenV;
}


int main(int argc, char** argv)
{
	//testCamera();

	//VectorD ux = Algebra::Ux;
	//ux[0] = 2.0; //works without changing the original!
	//std::cout << ux << std::endl;
	//return 0;


	GL::Window app;
	return app.Run();


	
}

