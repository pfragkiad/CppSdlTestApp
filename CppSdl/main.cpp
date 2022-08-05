#include "../Algebra/Algebra.h"
#include "Window.hpp"

#include "Examples.hpp"

#include <iostream>

using namespace GL;

void testCamera()
{
	Camera testCamera;
	testCamera.SetPosition(Algebra::Zero);
	testCamera.SetLookAt(2.0 * Algebra::Ux);
	testCamera.SetUp(Algebra::Uz);
	testCamera.SetLength(1.0);
	testCamera.SetHorizontalSize(1.0);
	testCamera.SetAspectRatio(1.0);
	testCamera.UpdateCameraGeometry();

	//get the screen center and U, V vectors and display
	VD screenCenter = testCamera.GetScreenCenter();
	VD screenU = testCamera.GetU();
	VD screenV = testCamera.GetV();
	std::cout
		<< "Center:\n" << screenCenter
		<< "\nU:\n" << screenU << "\nV:\n" << screenV;
}

void testUx()
{
	VD ux = Algebra::Ux;
	ux[0] = 2.0; //works without changing the original!
	std::cout << ux << std::endl;
}

int main(int argc, char** argv)
{
	//testCamera();
	//testUx();
	for (size_t i = 5; i-- > 0; )
		std::cout << i << endl;
	return 0;

	GL::Window app{ Examples::Scene3Spheres() };
	//GL::Window app{ Examples::SceneSphere() };
	return app.Run(true);



}

