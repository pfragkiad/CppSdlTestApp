#include "App.hpp"

#include <iostream>

using namespace GL;

void testCamera()
{
	Camera testCamera;
	testCamera.SetPosition(Vector<double>{0.0, 0.0, 0.0});
	testCamera.SetLookAt(Vector<double>{ 0.0, 2.0, 0.0 });
	testCamera.SetUp(Vector<double>{0.0, 0.0, 1.0});
	testCamera.SetLength(1.0);
	testCamera.SetHorizontalSize(1.0);
	testCamera.SetAspectRatio(1.0);
	testCamera.UpdateCameraGeometry();

	//get the screen center and U, V vectors and display
	Vector<double> screenCenter = testCamera.GetScreenCenter();
	Vector<double> screenU = testCamera.GetU();
	Vector<double> screenV = testCamera.GetV();
	std::cout
		<< "Center:\n" << screenCenter
		<< "\nU:\n" << screenU << "\nV:\n" << screenV;
}


int main(int argc, char** argv)
{
	//testCamera();

	GL::App app;
	return app.Run();
}

