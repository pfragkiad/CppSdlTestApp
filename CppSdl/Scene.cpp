#include "Scene.hpp"
#include "Image.hpp"
#include <iostream>
#include <vector>

#include <chrono>
#include <thread>
#include <numeric> //accumulate

#define USE_PARALLEL

using namespace GL;

//Each Scene subclass has its own 
Scene::Scene() {

}


void Scene::FillRow(int x, int ySize, float xFact, float yFact, Image& outputImage)
{
	//float xFact = 2.0f / xSize; //0 to 2
	//float yFact = 2.0f / ySize; //0 to 2

	for (int y = 0; y < ySize; y++)
	{
		//normalize the x and y coordinates
		float normX = static_cast<float>(x) * xFact - 1.0f; //-1 to 1
		float normY = static_cast<float>(y) * yFact - 1.0f; //-1 to 1
		Ray cameraRay;

		//generate the ray for this pixel
		_camera.GenerateRay(normX, normY, cameraRay);

		for (pShape currentObject : _objects)
		{
			VD intersectionPoint(3);
			VD localNormal(3);
			VD localColor(3);

			//test if we have a valid intersection
			bool validIntersection = currentObject->TestIntersection(
				cameraRay, intersectionPoint, localNormal, localColor);
			//if we have a valid intersection, change pixel color to red
			if (validIntersection)
			{
				//compute intensity of illumination
				double intensity;
				VD color;
				bool validIllumination = false;
				for (auto currentLight : _lights)
				{
					validIllumination = currentLight ->
						ComputeIllumination(intersectionPoint, localNormal,
							_objects, currentObject, color, intensity);
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
						localColor[0] * intensity,
						localColor[1] * intensity,
						localColor[2] * intensity);
#else
					//outputImage.SetPixel(x, y,
					//	localColor[0] * intensity,
					//	localColor[1] * intensity,
					//	localColor[2] * intensity);
					outputImage.tempPixels[y * outputImage._xSize + x] =
					TO_SDLCOLOR(
						localColor[0] * intensity,
						localColor[1] * intensity,
						localColor[2] * intensity);
#endif
				//else //leave pixel unchanged
				//	outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
			}
			//else //leave pixel unchanged
			//	outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
		}
	}
}

class Timer {
	std::chrono::steady_clock::time_point start;

	static inline std::vector<std::chrono::nanoseconds> _durations;
public:
	Timer() {
		start = std::chrono::high_resolution_clock::now();
	}
	~Timer() {
		auto duration = std::chrono::high_resolution_clock::now() - start;
		_durations.push_back(duration);
		//std::cout << std::chrono::duration_cast<std::chrono::seconds>(duration) << "\n";
		std::cout << "Current: " << std::chrono::duration_cast<std::chrono::milliseconds>(duration) << "\n";

		auto average = std::accumulate(_durations.cbegin(), _durations.cend(),
			decltype(_durations)::value_type(0)) / _durations.size();
		std::cout << "Average: " << std::chrono::duration_cast<std::chrono::milliseconds>(average) << "\n";

	}
};

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

	float xFact = 2.0f / xSize; //0 to 2
	float yFact = 2.0f / ySize; //0 to 2
	//double minDist = 1e6;
	//double maxDist = 0.0;

	std::vector<std::thread> threads;

	Timer timer;

	for (int x = 0; x < xSize; x++)
	{
		//std::cout << x << " of " << xSize << std::endl;

		//std::thread t([&] {RunY(x, ySize, xFact, yFact, outputImage); });

		//threads.emplace_back(t);
#ifdef USE_PARALLEL
		threads.push_back(thread(&Scene::FillRow, std::ref(*this), x, ySize, xFact, yFact, std::ref(outputImage)));
#else
		 //19.8 sec in serial, 2.8 in parallel
		FillRow(x, ySize, xFact, yFact, outputImage);
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
