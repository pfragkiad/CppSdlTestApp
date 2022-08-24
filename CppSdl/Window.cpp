
#include "GL.h"

using namespace GL;

//the constructor(defaut)
Window::Window()
{
	isRunning = true;
	pWindow = nullptr;
	pRenderer = nullptr;
}

Window::Window(std::shared_ptr<GL::Scene> scene)
{
	isRunning = true;
	pWindow = nullptr;
	pRenderer = nullptr;
	_scene = scene;
}

bool Window::OnInit(int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;

	pWindow = SDL_CreateWindow("Ray Tracing Stuff",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_SHOWN);

	if (pWindow == nullptr) return false;

	pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

	//initialize the Image instance
	_image.Initialize(width, height, pRenderer);

	//set the background color
	SDL_SetRenderDrawColor(pRenderer, 100, 255, 255, 255);

	return true;
}

int Window::Run(bool isImageStatic)
{
	return Run(1280, 720, isImageStatic);
}

int Window::Run(int width, int height, bool isImageStatic)
{
	//failure
	if (!OnInit(width, height)) return -1;

	if (isImageStatic)
	{
		OnRender(); //render once

		while (isRunning)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event) != 0)
				OnEvent(&event);

			OnLoop();
		}
	}
	else
	{
		while (isRunning)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event) != 0)
				OnEvent(&event);

			OnLoop();
			OnRender();
		}
	}
	//success
	return 0;
}

void Window::OnEvent(SDL_Event* event)
{
	if (event->type == SDL_QUIT)
		isRunning = false;
}


void Window::OnLoop() {}

void Window::OnRender()
{
	SDL_RenderClear(pRenderer);

	//render the scene
	//std::cout << "Rendering the scene...\n";

#ifndef USE_RGB_VECTORS
	_image.Reset(); //needed to reset the tempPixels
#endif

	_scene->Render(_image);
	//std::cout << "Done!\n";

	//display the image
	_image.Display();

	//show the result
	SDL_RenderPresent(pRenderer);
}


void Window::OnExit()
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
