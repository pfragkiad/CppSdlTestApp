#include "CImage.h"

CImage::CImage()
{
	m_xSize = 0;
	m_ySize = 0;
	m_pTexture = nullptr;
}

CImage::~CImage()
{
	if (m_pTexture != nullptr)
		SDL_DestroyTexture(m_pTexture);
	m_pTexture = nullptr;
}

//function to initialize
void CImage::Initialize(const int xSize, const int ySize, SDL_Renderer* pRenderer)
{
	//resize the image arrays
	m_rChannel.resize(xSize, std::vector<double>(ySize, 0.0));
	m_gChannel.resize(xSize, std::vector<double>(ySize, 0.0));
	m_bChannel.resize(xSize, std::vector<double>(ySize, 0.0));

	//store the dimensions
	m_xSize = xSize; m_ySize = ySize;

	//store the pointer to the renderer
	m_pRenderer = pRenderer;

	//initialize the texture
	InitTexture();
}

//funtion to set the colour of a pixel
void CImage::SetPixel(const int x, const int y, const double red, const double green, const double blue)
{
	m_rChannel.at(x).at(y) = red;
	m_gChannel.at(x).at(y) = green;
	m_bChannel.at(x).at(y) = blue;
}

//function to generate the display
void CImage::Display()
{
	//allocate memory for a pixel buffer
	Uint32* tempPixels = new Uint32[(size_t)m_xSize * (size_t)m_ySize];

	//clear the pixel buffer
	memset(tempPixels, 0, (size_t)m_xSize * (size_t)m_ySize);

	for (int x = 0; x < m_xSize; ++x)
		for (int y = 0; y < m_ySize; ++y)
			tempPixels[y * m_xSize + x] = ConvertColor(
				m_rChannel.at(x).at(y),
				m_gChannel.at(x).at(y),
				m_bChannel.at(x).at(y));

	//update the texture with the pixel buffer
	SDL_UpdateTexture(m_pTexture, nullptr, tempPixels, m_xSize * sizeof(Uint32));

	//delete the pixel buffer
	delete[] tempPixels;

	//copy the texture to the renderer
	SDL_Rect srcRect, bounds;
	srcRect.x = srcRect.y = 0;
	srcRect.w = m_xSize;
	srcRect.h = m_ySize;
	bounds = srcRect;
	SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &bounds);
}

//function to initialize the texture
void CImage::InitTexture()
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
	if (m_pTexture != nullptr)
		SDL_DestroyTexture(m_pTexture);

	//create the texture that will store the image
	SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32, rmask, gmask, bmask, amask);
	m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}

Uint32 CImage::ConvertColor(const double red, const double green, const double blue)
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
