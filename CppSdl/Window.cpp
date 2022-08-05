#include "Window.hpp"
#include "../Algebra/Vector.h"

using namespace GL;

//the constructor(defaut)
Window::Window()
{
	isRunning = true;
	pWindow = nullptr;
	pRenderer = nullptr;
}

Window::Window(Scene scene)
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

	pWindow = SDL_CreateWindow("qbRayTracer!",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_SHOWN);

	if (pWindow == nullptr) return false;

	pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

	//initialize the Image instance
	_image.Initialize(width, height, pRenderer);


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
	//set the background color
	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	SDL_RenderClear(pRenderer);

	//render the scene
	std::cout << "Rendering the scene...";
	_scene.Render(_image);
	std::cout << "\nDone!\n";

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
