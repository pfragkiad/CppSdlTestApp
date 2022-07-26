#include "CApp.h"



//the constructor(defaut)
CApp::CApp()
{
	isRunning = true;
	pWindow = nullptr;
	pRenderer = nullptr;
}

bool CApp::OnInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;

	pWindow = SDL_CreateWindow("qbRayTracer!",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1280, 720, SDL_WINDOW_SHOWN);

	if (pWindow == nullptr) return false;

	pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

	//initialize the CImage instance
	m_image.Initialize(1280, 720, pRenderer);

	//create some color variations
	for (int x = 0; x < 1280; ++x)
		for (int y = 0; y < 720; ++y)
		{
			double red = static_cast<double>(x) / 1280.0 * 255.0;
			double green = static_cast<double>(y) / 720.0 * 255.0;
			m_image.SetPixel(x, y, red, green, 0.0);
		}

	return true;
}

int CApp::OnExecute()
{
	//failure
	if (!OnInit()) return -1;

	while (isRunning)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0)
			OnEvent(&event);

		OnLoop();
		OnRender();
	}
	//success
	return 0;
}

void CApp::OnEvent(SDL_Event* event)
{
	if (event->type == SDL_QUIT)
		isRunning = false;
}


void CApp::OnLoop() {}



void CApp::OnRender()
{
	//set the background color
	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	SDL_RenderClear(pRenderer);

	//display the image
	m_image.Display();

	//show the result
	SDL_RenderPresent(pRenderer);
}


void CApp::OnExit()
{
	//tidy up SDL2 stuff
	if (pRenderer != nullptr)
		SDL_DestroyRenderer(pRenderer);
	if (pWindow != nullptr)
		SDL_DestroyWindow(pWindow);

	pWindow = nullptr;
	pRenderer = nullptr;

	SDL_Quit();

}
