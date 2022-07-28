#ifndef Image_H
#define Image_H

#include <string>
#include <vector>
#include <SDL.h>

namespace GL
{
	class Image
	{
	public:

		//constructor
		Image();

		//destructor
		~Image();

		//function to initialize
		void Initialize(const int xSize, const int ySize, SDL_Renderer* pRenderer);

		//funtion to set the colour of a pixel
		void SetPixel(const int x, const int y, const double red, const double green, const double blue);

		void Display();

		inline int GetXSize() { return _xSize; }
		inline int GetYSize() { return _ySize; }

	private:
		Uint32 ConvertColor(const double red, const double green, const double blue);

		void InitTexture();

		//arrays to store image data
		std::vector<std::vector<double>> _rChannel;
		std::vector<std::vector<double>> _gChannel;
		std::vector<std::vector<double>> _bChannel;

		//store the dimensions of the image
		int _xSize, _ySize;

		//SDL2 stuff
		SDL_Renderer* _pRenderer;
		SDL_Texture* _pTexture;

	};
}

#endif
