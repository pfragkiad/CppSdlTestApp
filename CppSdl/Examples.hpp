#ifndef EXAMPLES_H
#define EXAMPLES_H

#include "Image.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"

#include "Random.h"
#include "Colors.h"

#include "Scene3Spheres.hpp"
#include "SceneSphere.h"
#include "SceneMultiSpheres.h"





namespace GL::Examples
{
	inline void Example1Simple2ColorImage(Image& image)
	{
		int xSize = image.GetXSize();
		int ySize = image.GetYSize();
		//create some color variations
		for (int x = 0; x < xSize; x++)
			for (int y = 0; y < ySize; ++y)
			{
				double red = static_cast<double>(x) / 1280.0 * 255.0;
				double green = static_cast<double>(y) / 720.0 * 255.0;
				image.SetPixel(x, y, red, green, 0.0);
			}
	}

	


	inline void Example2SimpleSphere(Image& image, Camera& camera, Sphere& sphere)
	{
		int xSize = image.GetXSize();
		int ySize = image.GetYSize();

		////create some color variations
		//Examples::Example1Simple2ColorImage(outputImage);

		////loop over each pixel in our image
		//Vector<double> intersectionPoint(3);
		//Vector<double> localNormal(3);
		//Vector<double> localColor(3);

		float xFact = 2.0f / xSize; //0 to 2
		float yFact = 2.0f / ySize; //0 to 2
		double minDist = 1e6;
		double maxDist = 0.0;

		int r = random(0, 255);
		int g = random(0, 255);
		int b = random(0, 255);

		for (int x = 0; x < xSize; x++) {
			//normalize the x and y coordinates
			float normX = x * xFact - 1.0f; //-1 to 1
			
			for (int y = 0; y < ySize; y++)
			{
				float normY = y * yFact - 1.0f; //-1 to 1

				//Ray cameraRay;
				////generate the ray for this pixel
				//camera.GenerateRay(normX, normY, cameraRay);
				Ray cameraRay = camera.GenerateRay(normX, normY);

				//test if we have a valid intersection
				IntersectionInfo intersection = sphere.TestIntersection(cameraRay);
				//if we have a valid intersection, change pixel color to red
				if (intersection.Valid)
				{
					//compute the distance between the camera and the point of intersection
					double distance = (intersection.Point - cameraRay.GetPoint1()).Length();
					if (distance > maxDist) maxDist = distance;
					else if (distance < minDist) minDist = distance;

					double ratio = (distance - 9.0) / 0.94605; // = (distance - minDistance)/ (maxDistance-minDistance)
					image.SetPixel(x, y, 255.0 - 255 * ratio, g, b);
				}
				else
					image.SetPixel(x, y, 0.0, 0.0, 0.0);
			}
		}

		//minimum is 9.0
		//maximum is 9.94605
		std::cout << "Minimum distance: " << minDist << std::endl;
		std::cout << "Maximum distance: " << maxDist << std::endl;
	}

}



#endif