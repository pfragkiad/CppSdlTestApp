#include "Scene.hpp"
#include "Examples.hpp"

using namespace GL;

Scene::Scene() {
	//configure the camera
	_camera.SetPosition(VectorD{0.0, -10.0, 0.0});
	_camera.SetLookAt(VectorD{0.0, 0.0, 0.0});
	_camera.SetUp(VectorD{0.0, 0.0, 1.0});
	_camera.SetHorizontalSize(0.25);
	_camera.SetAspectRatio(1280.0 / 720.0);
	_camera.UpdateCameraGeometry();

	//construct a test sphere
	_objects.push_back(std::make_shared<Sphere>(Sphere()));

	//construct a test light
	_lights.push_back(std::make_shared<PointLight>(PointLight()));
	_lights.at(0)->_location = VectorD{ 0.0,0.0,10.0 };//VectorD{ 10.0,-5.0,10.0 };
	_lights.at(0)->_color = VectorD{ 255.0,255.0,255.0 };
	_lights.at(0)->_intensity = 1.0;
}

//function to perform the rendering
bool Scene::Render(Image& outputImage)
{
	////create some color variations
	//Examples::Example1Simple2ColorImage(outputImage);

	//Examples::Example2SimpleSphere(outputImage, _camera, _testSphere);
	//Examples::Example2SimpleSphere(outputImage,
	//	_camera, _objects.at(0)
	//	)
	//	;
	int xSize = outputImage.GetXSize();
	int ySize = outputImage.GetYSize();

	////create some color variations
	//Examples::Example1Simple2ColorImage(outputImage);

	//loop over each pixel in our image
	Ray cameraRay;
	VectorD intersectionPoint(3);
	VectorD localNormal(3);
	VectorD localColor(3);

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

			for (auto currentObject : _objects)
			{
				//test if we have a valid intersection
				bool validIntersection = currentObject->TestIntersection(
					cameraRay, intersectionPoint, localNormal, localColor);
				//if we have a valid intersection, change pixel color to red
				if (validIntersection)
				{
					//compute intensity of illumination
					double intensity;
					VectorD color;
					bool validIllumination = false;
					for (auto currentLight : _lights)
					{
						validIllumination = currentLight ->
							ComputeIllumination(intersectionPoint, localNormal,
								_objects, currentObject, color, intensity);
						//std::cout << "Intensity: " << intensity << std::endl;
					}

					//compute the distance between the camera and the point of intersection
					double distance = (intersectionPoint - cameraRay._point1).norm();
					if (distance > maxDist) maxDist = distance;
					else if (distance < minDist) minDist = distance;

					//double ratio = (distance - 9.0) / 0.94605; // = (distance - minDistance)/ (maxDistance-minDistance)
					//outputImage.SetPixel(x, y, 255.0 - 255 * ratio, 0, 0.0);
					if (validIllumination)
						outputImage.SetPixel(x,y,255.0*intensity,0.0,10.0);
					
					else 
						outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
				}
				else
					outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
			}
		}

	//minimum is 9.0
	//maximum is 9.94605
	std::cout << "Minimum distance: " << minDist << std::endl;
	std::cout << "Maximum distance: " << maxDist << std::endl;

	return true;
}
