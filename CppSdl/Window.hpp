#pragma once

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
		Window(std::shared_ptr<GL::Scene> scene);

		int Run(bool isImageStatic);
		int Run(int width, int height, bool isImageStatic);
		//bool OnInit();
		bool OnInit(int width, int height);
		void OnEvent(SDL_Event* event);
		void OnLoop();
		void OnRender();
		void OnExit();

	private:
		//instance of the image
		Image _image;

		//unsigned long long _time;

		//instance of the scene class
		//Scene* _scene;
		std::shared_ptr<GL::Scene> _scene;
			
		Camera _camera;

		// SDL2 stuff
		bool isRunning;
		SDL_Window* pWindow;
		SDL_Renderer* pRenderer;
	};
}
