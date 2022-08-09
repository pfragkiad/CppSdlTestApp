#pragma once

#include <string>
#include <vector>
#include <array>
#include <SDL.h>

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define TO_SDLCOLOR(r,g,b) ((unsigned char)(r) << 24u) + ((unsigned char)(g) << 16u) + ((unsigned char)(b) << 8u) + 255u;
#else
#define TO_SDLCOLOR(r,g,b) (255u << 24u) + ((unsigned char)(r) << 16u) + ((unsigned char)(g) << 8u) + (unsigned char)(b); //he has bgr inversed here
#endif

#define GET_PIXELS_INDEX(x,y) y * _xSize + x

namespace GL
{
	class Image
	{
		friend class Scene;
	public:

		//constructor
		Image();

		//destructor
		~Image();

		//function to initialize
		void Initialize(const int xSize, const int ySize, SDL_Renderer* pRenderer);

#ifndef USE_RGB_VECTORS
		void Reset(); //resets the tempPixels array
#endif

		//funtion to set the colour of a pixel
		void SetPixel(const int x, const int y, const double red, const double green, const double blue);
		
		void Display() const;

		inline int GetXSize() const { return _xSize; }
		inline int GetYSize() const { return _ySize; }

	private:
		static Uint32 ConvertColor(const double red, const double green, const double blue);

		void InitTexture();

		//arrays to store image data
#ifdef USE_RGB_VECTORS
		std::vector<std::vector<double>> _rChannel;
		std::vector<std::vector<double>> _gChannel;
		std::vector<std::vector<double>> _bChannel;
#else
		Uint32* tempPixels = nullptr;
#endif
		
		//store the dimensions of the image
		int _xSize, _ySize;

		//SDL2 stuff
		SDL_Renderer* _pRenderer;
		SDL_Texture* _pTexture;

	};
}
