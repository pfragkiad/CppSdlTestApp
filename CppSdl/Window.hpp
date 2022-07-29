#ifndef App_H
#define App_H

//#pragma comment(lib,"SDL2.lib")
//#pragma comment(lib,"SDL2main.lib")
//#pragma comment(lib,"SDL2test.lib")
#include <SDL.h>
#include "Image.hpp"
#include "Scene.hpp"
#include "Camera.hpp"

namespace GL
{

	class Window
	{
	public:
		Window();

		int Run();
		int Run(int width, int height);
		//bool OnInit();
		bool OnInit(int width, int height);
		void OnEvent(SDL_Event* event);
		void OnLoop();
		void OnRender();
		void OnExit();

	private:
		//instance of the image
		Image _image;

		//instance of the scene class
		Scene _scene;

		Camera _camera;

		// SDL2 stuff
		bool isRunning;
		SDL_Window* pWindow;
		SDL_Renderer* pRenderer;
	};
}

#endif