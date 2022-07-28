#include "Image.hpp"

using namespace GL;

Image::Image()
{
	_xSize = 0;
	_ySize = 0;
	_pTexture = nullptr;
}

Image::~Image()
{
	if (_pTexture != nullptr)
		SDL_DestroyTexture(_pTexture);
	_pTexture = nullptr;
}

//function to initialize
void Image::Initialize(const int xSize, const int ySize, SDL_Renderer* pRenderer)
{
	//resize the image arrays
	_rChannel.resize(xSize, std::vector<double>(ySize, 0.0));
	_gChannel.resize(xSize, std::vector<double>(ySize, 0.0));
	_bChannel.resize(xSize, std::vector<double>(ySize, 0.0));

	//store the dimensions
	_xSize = xSize; _ySize = ySize;

	//store the pointer to the renderer
	_pRenderer = pRenderer;

	//initialize the texture
	InitTexture();
}

//funtion to set the colour of a pixel
void Image::SetPixel(const int x, const int y, const double red, const double green, const double blue)
{
	_rChannel.at(x).at(y) = red;
	_gChannel.at(x).at(y) = green;
	_bChannel.at(x).at(y) = blue;
}

//function to generate the display
void Image::Display()
{
	//allocate memory for a pixel buffer
	Uint32* tempPixels = new Uint32[(size_t)_xSize * (size_t)_ySize];

	//clear the pixel buffer
	memset(tempPixels, 0, (size_t)_xSize * (size_t)_ySize);

	for (int x = 0; x < _xSize; ++x)
		for (int y = 0; y < _ySize; ++y)
			tempPixels[y * _xSize + x] = ConvertColor(
				_rChannel.at(x).at(y),
				_gChannel.at(x).at(y),
				_bChannel.at(x).at(y));

	//update the texture with the pixel buffer
	SDL_UpdateTexture(_pTexture, nullptr, tempPixels, _xSize * sizeof(Uint32));

	//delete the pixel buffer
	delete[] tempPixels;

	//copy the texture to the renderer
	SDL_Rect srcRect, bounds;
	srcRect.x = srcRect.y = 0;
	srcRect.w = _xSize;
	srcRect.h = _ySize;
	bounds = srcRect;
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
	//convert the colours to unsigned integers
	unsigned char r = static_cast<unsigned char>(red);
	unsigned char g = static_cast<unsigned char>(green);
	unsigned char b = static_cast<unsigned char>(blue);


#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	Uint32 pixelColor = (r << 24) + (g << 16) + (b << 8) + 255;
#else
	Uint32 pixelColor = (255 << 24) + (r << 16) + (g << 8) + b;
#endif
	
	return pixelColor;
}
