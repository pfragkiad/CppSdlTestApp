#ifndef EXAMPLES_H
#define EXAMPLES_H

#include "Image.hpp"

namespace GL
{
	namespace Examples
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

	}

}

#endif