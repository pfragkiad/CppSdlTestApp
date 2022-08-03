#include "Examples.hpp"

std::random_device rd;
std::mt19937 gen(rd());

int random(int low, int high)
{
	std::uniform_int_distribution<> dist(low, high);
	return dist(gen);
}

void GL::Examples::Example2SimpleSphere(Image& image, Camera& camera, Sphere& sphere)
{
	int xSize = image.GetXSize();
	int ySize = image.GetYSize();

	////create some color variations
	//Examples::Example1Simple2ColorImage(outputImage);

	//loop over each pixel in our image
	Ray cameraRay;
	Vector<double> intersectionPoint(3);
	Vector<double> localNormal(3);
	Vector<double> localColor(3);

	double xFact = 2.0 / xSize; //0 to 2
	double yFact = 2.0 / ySize; //0 to 2
	double minDist = 1e6;
	double maxDist = 0.0;

	int r = random(0, 255);
	int g = random(0, 255);
	int b = random(0, 255);

	for (int x = 0; x < xSize; x++)
		for (int y = 0; y < ySize; y++)
		{
			//normalize the x and y coordinates
			double normX = x * xFact - 1.0; //-1 to 1
			double normY = y * yFact - 1.0; //-1 to 1

			//generate the ray for this pixel
			camera.GenerateRay(normX, normY, cameraRay);

			//test if we have a valid intersection
			bool validIntersection = sphere.TestIntersection(
				cameraRay, intersectionPoint, localNormal, localColor);
			//if we have a valid intersection, change pixel color to red
			if (validIntersection)
			{
				//compute the distance between the camera and the point of intersection
				double distance = (intersectionPoint - cameraRay._point1).norm();
				if (distance > maxDist) maxDist = distance;
				else if (distance < minDist) minDist = distance;

				double ratio = (distance - 9.0) / 0.94605; // = (distance - minDistance)/ (maxDistance-minDistance)
				image.SetPixel(x, y, 255.0 - 255 * ratio, g, b);
			}
			else
				image.SetPixel(x, y, 0.0, 0.0, 0.0);
		}

	//minimum is 9.0
	//maximum is 9.94605
	std::cout << "Minimum distance: " << minDist << std::endl;
	std::cout << "Maximum distance: " << maxDist << std::endl;
}