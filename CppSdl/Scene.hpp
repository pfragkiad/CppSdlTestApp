#ifndef CSCENE_H
#define CSCENE_H

#include <memory>
#include <vector>
#include <SDL.h>
#include "Image.hpp"

#include "Camera.hpp"
#include "Sphere.hpp"

namespace GL
{
	class Scene
	{
	public:
		//the default constructor
		Scene();

		//function to perform the rendering
		bool Render(Image& outputImage);

	private:
		Camera _camera; 

		////a unit sphere on the origin
		//Sphere _testSphere;

		//The list of objects in the scene
		std::vector<std::shared_ptr<GL::Shape>> _objects;
	};
}

#endif