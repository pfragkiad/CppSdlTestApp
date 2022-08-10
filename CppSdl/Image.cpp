#include "GL.h"

using namespace GL;

Image::Image()
{
	_xSize = 0;
	_ySize = 0;
	_pTexture = nullptr;
	_pRenderer = nullptr;
#ifndef USE_RGB_VECTORS
	tempPixels = nullptr;
#endif
}

Image::~Image()
{
#ifndef USE_RGB_VECTORS
	if (tempPixels != nullptr)
		delete[] tempPixels;
#endif

	if (_pTexture != nullptr)
		SDL_DestroyTexture(_pTexture);
	_pTexture = nullptr;
}

//needed only if data is passed
#ifndef USE_RGB_VECTORS
void Image::Reset()
{
	if (tempPixels == nullptr)
	{
		//we assume that the size does not change 
		//delete[] tempPixels;
		tempPixels = new Uint32[(size_t)(_xSize * _ySize)];
	}

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	Uint32 pixelColor = 255u;
#else
	const Uint32 pixelColor = 255u << 24u; //he has bgr inversed here
#endif

	std::fill(tempPixels, tempPixels + _xSize * _ySize, pixelColor);
	//memset(tempPixels, pixelColor, (size_t)(_xSize * _ySize)); //memset DOES NOT WORK

}
#endif

//function to initialize
void Image::Initialize(const int xSize, const int ySize, SDL_Renderer* pRenderer)
{
	//store the dimensions
	_xSize = xSize; _ySize = ySize;

#ifdef USE_RGB_VECTORS
	//resize the image arrays
	_rChannel.resize(xSize, std::vector<double>(ySize, 0.0));
	_gChannel.resize(xSize, std::vector<double>(ySize, 0.0));
	_bChannel.resize(xSize, std::vector<double>(ySize, 0.0));
#endif

	//store the pointer to the renderer
	_pRenderer = pRenderer;

	//initialize the texture
	InitTexture();
}

//funtion to set the colour of a pixel
void Image::SetPixel(const int x, const int y, const double red, const double green, const double blue)
{


#ifdef USE_RGB_VECTORS
	//_rChannel.at(x).at(y) = red;
	//_gChannel.at(x).at(y) = green;
	//_bChannel.at(x).at(y) = blue;	

	_rChannel[x][y] = red;
	_gChannel[x][y] = green;
	_bChannel[x][y] = blue;
#else
	tempPixels[GET_PIXELS_INDEX(x,y,_xSize,_ySize)] = TO_SDLCOLOR(red, green, blue); //ConvertColor(red, green, blue);
#endif
}

//function to generate the display
void Image::Display() const
{
#ifdef USE_RGB_VECTORS
	//allocate memory for a pixel buffer
	Uint32* tempPixels = new Uint32[(size_t)_xSize * (size_t)_ySize];

	//clear the pixel buffer
	//memset(tempPixels, 0, (size_t)_xSize * (size_t)_ySize);
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	Uint32 pixelColor = 255u;
#else
	const Uint32 pixelColor = 255u << 24u; //he has bgr inversed here
#endif
	std::fill(tempPixels, tempPixels + (size_t)(_xSize * _ySize),pixelColor);

	for (size_t x = 0; x < _xSize; ++x)
		for (size_t y = 0; y < _ySize; ++y)
		{
			size_t index = GET_PIXELS_INDEX(x, y, _xSize, _ySize);
			SDL_assert(index< (size_t)(_xSize* _ySize));

			tempPixels[index] = ConvertColor(
				_rChannel[x][y], _gChannel[x][y], _bChannel[x][y]);
		}
#endif

	//update the texture with the pixel buffer
	SDL_UpdateTexture(_pTexture, nullptr, tempPixels, _xSize * sizeof(Uint32));

	////delete the pixel buffer
	//delete[] tempPixels;

	//copy the texture to the renderer
	SDL_Rect srcRect{ 0,0,_xSize,_ySize }, bounds{ srcRect };
	//srcRect.x = srcRect.y = 0;
	//srcRect.w = _xSize; srcRect.h = _ySize;
	//bounds = srcRect;

	SDL_RenderCopy(_pRenderer, _pTexture, &srcRect, &bounds);
}

//function to initialize the texture
void Image::InitTexture()
{
	//initilize the texture
	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER ==SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	//delete any previously created texture
	if (_pTexture != nullptr)
		SDL_DestroyTexture(_pTexture);

	//create the texture that will store the image
	SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, _xSize, _ySize, 32, rmask, gmask, bmask, amask);
	_pTexture = SDL_CreateTextureFromSurface(_pRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}

Uint32 Image::ConvertColor(const double red, const double green, const double blue)
{
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	return ((unsigned char)red << 24u) + ((unsigned char)green << 16u) + ((unsigned char)blue << 8u) + 255u;
#else
	return (255u << 24u) + ((unsigned char)red << 16u) + ((unsigned char)green << 8u) + (unsigned char)blue; //he has bgr inversed here
#endif

	//return pixelColor;
}
