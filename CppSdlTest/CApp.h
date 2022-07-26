#pragma once

//#pragma comment(lib,"SDL2.lib")
//#pragma comment(lib,"SDL2main.lib")
//#pragma comment(lib,"SDL2test.lib")
#include <SDL.h>
#include "CImage.h"

class CApp
{
public:
	CApp();

	int OnExecute();
	bool OnInit();
	void OnEvent(SDL_Event* event);
	void OnLoop();
	void OnRender();
	void OnExit();

private:
	//instance of the image
	CImage m_image;

	// SDL2 stuff
	bool isRunning;
	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;
};
