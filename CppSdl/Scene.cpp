#include "Scene.hpp"
#include "Examples.hpp"

using namespace GL;

Scene::Scene() {
	//configure the camera
	_camera.SetPosition(Vector<double>{0.0, -10.0, 0.0});
	_camera.SetLookAt(Vector<double>{0.0, 0.0, 0.0});
	_camera.SetUp(Vector<double>{0.0, 0.0, 1.0});
	_camera.SetHorizontalSize(0.25);
	_camera.SetAspectRatio(1280.0 / 720.0);
	_camera.UpdateCameraGeometry();
}

//function to perform the rendering
bool Scene::Render(Image& outputImage)
{
	int xSize = outputImage.GetXSize();
	int ySize = outputImage.GetYSize();

	////create some color variations
	//Examples::Example1Simple2ColorImage(outputImage);

	//loop over each pixel in our image
	Ray cameraRay;
	Vector<double> intPoint(3);
	Vector<double> localNormal(3);
	Vector<double> localColor(3);

	double xFact = 2.0 / xSize; //0 to 2
	double yFact = 2.0 / ySize; //0 to 2
	double minDist = 1e6;
	double maxDist = 0.0;
	for (int x = 0; x < xSize; x++)
		for (int y = 0; y < ySize; y++)
		{
			//normalize the x and y coordinates
			double normX = x * xFact - 1.0; //-1 to 1
			double normY = y * yFact - 1.0; //-1 to 1

			//generate the ray for this pixel
			_camera.GenerateRay(normX, normY, cameraRay);

			//test if we have a valid intersection
			bool validInt = _testSphere.TestIntersection(
				cameraRay, intPoint, localNormal, localColor);
			//if we have a valid intersection, change pixel color to red
			if (validInt)
				outputImage.SetPixel(x, y, 255.0, 0.0, 0.0);
			else
				outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
		}

	return true;
}
