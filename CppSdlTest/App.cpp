#include "App.hpp"
#include "Examples.hpp"

using namespace GL;

//the constructor(defaut)
App::App()
{
	isRunning = true;
	pWindow = nullptr;
	pRenderer = nullptr;
}

bool App::OnInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;

	pWindow = SDL_CreateWindow("qbRayTracer!",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1280, 720, SDL_WINDOW_SHOWN);

	if (pWindow == nullptr) return false;

	pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

	//initialize the Image instance
	m_image.Initialize(1280, 720, pRenderer);

	//Examples::Example1Simple2ColorImage(m_image);
	m_scene.Render(m_image);

	return true;
}

int App::OnExecute()
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

void App::OnEvent(SDL_Event* event)
{
	if (event->type == SDL_QUIT)
		isRunning = false;
}


void App::OnLoop() {}



void App::OnRender()
{
	//set the background color
	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	SDL_RenderClear(pRenderer);

	//render the scene
	m_scene.Render(m_image);

	//display the image
	m_image.Display();
	
	//show the result
	SDL_RenderPresent(pRenderer);
}


void App::OnExit()
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
