#include "App.hpp"
#include "Examples.hpp"
#include "../Algebra/Vector.h"

using namespace GL;

//the constructor(defaut)
App::App()
{
	isRunning = true;
	pWindow = nullptr;
	pRenderer = nullptr;
}

//bool App::OnInit()
//{
//	return OnInit(1280, 720);
//}

bool App::OnInit(int width, int height)
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

	//set the background color to white
	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	SDL_RenderClear(pRenderer);

	//Examples::Example1Simple2ColorImage(_image);
	_scene.Render(_image);
	
	//display the result
	_image.Display();

	//show the result
	SDL_RenderPresent(pRenderer);



	return true;
}

int App::Run()
{
	return Run(1280, 720);
}

int App::Run(int width, int height)
{
	//failure
	if (!OnInit(width,height)) return -1;

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
	////set the background color
	//SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	//SDL_RenderClear(pRenderer);

	////render the scene
	//_scene.Render(_image);

	////display the image
	//_image.Display();
	//
	////show the result
	//SDL_RenderPresent(pRenderer);
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
