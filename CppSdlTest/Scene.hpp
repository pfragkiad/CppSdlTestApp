#ifndef CSCENE_H
#define CSCENE_H

#include <vector>
#include <SDL.h>
#include "Image.hpp"

namespace GL
{
	class Scene
	{
	public:
		//the default constructor
		Scene();

		//function to perform the rendering
		bool Render(Image& outputImage);
	};
}

#endif