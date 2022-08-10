#include "Scene.hpp"
#include "Image.hpp"
#include <iostream>
#include <vector>

#include <chrono>
#include <thread>
#include <numeric> //accumulate

#include "Timer.h"
#include <cmath>

#define USE_PARALLEL

using namespace GL;

//Each Scene subclass has its own 
Scene::Scene() {

}


void Scene::FillRow(int x, float normX, int ySize, float yFact, Image& outputImage)
{
	for (int y = 0; y < ySize; y++)
	{
		//if (x == 1280 / 2 && y == 720 / 2)
		//{
		//	SDL_assert(false);
		//}
		float normY = static_cast<float>(y) * yFact - 0.5f; //-0.5 to 0.5 (changed by me)

		//Ray cameraRay;

		//generate the ray for this pixel
		//_camera.GenerateRay(normX, normY, cameraRay);
		Ray cameraRay = _camera.GenerateRay(normX, normY);

		//SDL_assert(!(  abs(cameraRay.GetLab()[1]- 0.1)<=1e-3  && normX == 0.0f));

		for (pShape currentObject : _objects)
		{
			//VD intersectionPoint(3);
			//VD localNormal(3);
			//VD localColor(3);
			//test if we have a valid intersection
			//bool validIntersection = currentObject->TestIntersection(
			//	cameraRay, intersectionPoint, localNormal, localColor);
			IntersectionInfo intersection = currentObject->TestIntersection(cameraRay);

			//if we have a valid intersection, change pixel color to red
			//if (validIntersection)
			if (intersection.Valid)
			{
				//compute intensity of illumination
				double intensity; VD color;
				bool validIllumination = false;

				for (auto currentLight : _lights)
				{
					//validIllumination = currentLight ->
					//	ComputeIllumination(intersectionPoint, localNormal,
					//		_objects, currentObject, color, intensity);
					validIllumination = currentLight ->
						ComputeIllumination(intersection, _objects, currentObject, color, intensity);

					intersection.Color *= intensity;

					//std::cout << "Intensity: " << intensity << std::endl;
				}

				////compute the distance between the camera and the point of intersection
				//double distance = (intersectionPoint - cameraRay._point1).norm();
				//if (distance > maxDist) maxDist = distance;
				//else if (distance < minDist) minDist = distance;

				//double ratio = (distance - 9.0) / 0.94605; // = (distance - minDistance)/ (maxDistance-minDistance)
				//outputImage.SetPixel(x, y, 255.0 - 255 * ratio, 0, 0.0);
				if (validIllumination)
					//outputImage.SetPixel(x, y, 255.0 * intensity, 0.0, 10.0);


#ifdef USE_RGB_VECTORS
					outputImage.SetPixel(x, y,
						intersection.Color[0],
						intersection.Color[1],
						intersection.Color[2]);
#else
					//outputImage.SetPixel(x, y,
					//	localColor[0] * intensity,
					//	localColor[1] * intensity,
					//	localColor[2] * intensity);
					outputImage.tempPixels
					[GET_PIXELS_INDEX(x, y, outputImage._xSize, outputImage._ySize)] =
					TO_SDLCOLOR(
						intersection.Color[0],
						intersection.Color[1],
						intersection.Color[2]);
#endif
				//else //leave pixel unchanged
				//	outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
			}
			//else //leave pixel unchanged
			//	outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
		}
	}
}

void GL::Scene::ProceedTime()
{
}


//function to perform the rendering
bool Scene::Render(Image& outputImage)
{

	Timer<10> timer;

	ProceedTime(); //useful for animation purposes

	int xSize = outputImage._xSize;
	int ySize = outputImage._ySize;

	//loop over each pixel in our image

	float xFact = 1.0f / xSize; //0 to 1 //changed by me
	float yFact = 1.0f / ySize; //0 to 1 //changed by me
	//double minDist = 1e6;
	//double maxDist = 0.0;

	std::vector<std::thread> threads;
	for (int x = 0; x < xSize; x++)
	{
		//std::cout << x << " of " << xSize << std::endl;

		//normalize x coordinate
		float normX = static_cast<float>(x) * xFact - 0.5f; //-0.5 to 0.5 (changed by me)

#ifdef USE_PARALLEL
		threads.push_back(thread(&Scene::FillRow, std::ref(*this), x, normX, ySize, yFact, std::ref(outputImage)));
#else
		//19.8 sec in serial, 2.8 in parallel, 0.2 in parallel + static array instead of std::vector within Vector<T>
		FillRow(x, normX, ySize, yFact, outputImage);
#endif

	}
#ifdef USE_PARALLEL
	for (auto& th : threads)
		th.join();
#endif
	////minimum is 9.0
	////maximum is 9.94605
	//std::cout << "Minimum distance: " << minDist << std::endl;
	//std::cout << "Maximum distance: " << maxDist << std::endl;

	return true;
}
