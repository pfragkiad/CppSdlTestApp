#include "../Algebra/Algebra.h"
#include "Window.hpp"

#include "Examples.hpp"

#include <iostream>

using namespace GL;

void testCamera()
{
	Camera testCamera;
	testCamera.SetPosition(VDs::Zero);
	testCamera.SetLookAt(2.0 * VDs::Ux);
	testCamera.SetUp(VDs::Uz);
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
	VD ux = VDs::Ux;
	ux[0] = 2.0; //works without changing the original!
	std::cout << ux << std::endl;
}

void testLoops()
{
	for (size_t i = 5; i != numeric_limits<size_t>::max(); i--)
		std::cout << i << endl;

	size_t i = 5; do
	{
		std::cout << i << endl;
	} while (i-- != 0);
}

int main(int argc, char** argv)
{
	testCamera();
	//testUx();

	GL::Window app{ Examples::Scene3Spheres() };
	//GL::Window app{ Examples::SceneSphere() };
	return app.Run(true);



}

