#include "Scene.hpp"
#include "Examples.hpp"

using namespace GL;

Scene::Scene() {}

//function to perform the rendering
bool Scene::Render(Image& outputImage)
{
	////get the dimensions of the output image
	//int xSize = outputImage.GetXSize();
	//int ySize = outputImage.GetYSize();

	//create some color variations
	Examples::Example1Simple2ColorImage(outputImage);

	return true;
}
