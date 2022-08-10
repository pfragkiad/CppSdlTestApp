#pragma once

#include "Scene.hpp"
#include <SDL.h> //MI_P
#include <cmath>
#include "Random.h"
#include "Colors.h"

namespace GL::Examples
{

	class SceneMultiSpheres : public Scene
	{
	public:
		//only inline is accepted and separate cpp definition.
		//if the definition is below then it is not accepted
		SceneMultiSpheres(int count);

		SceneMultiSpheres();


		void ProceedTime() override;
	};

	inline SceneMultiSpheres::SceneMultiSpheres() : SceneMultiSpheres(10) {}


	//inline is obligatory or else "duplicate definitions" will be reported by the compiler
	inline SceneMultiSpheres::SceneMultiSpheres(int count)
	{
		//configure the camera
		_camera.SetProjectionScreen(/*cameraLength*/ 1.0,/*horizontalSize*/ 1.0, /*aspect ratio*/ 1280.0 / 720.0);
		_camera.SetCamera(/*position*/ VD{ 0.0, -10.0, 0.0 }, /*look at*/ VD{ 0.0, 0.0, 0.0 }, /*up vector*/ VD{ 0.0, 0.0, 1.0 });

		for (int i = 0; i < count; i++)
			_objects.push_back(std::make_shared<Sphere>(
				Sphere(
					/*radius*/ random(0.1, 0.8),
					/*basecolor*/ VD{ random(0.0,250.0), random(0.0,250.0), random(0.0,250.0) },
					/*Translation*/ VD{ random(-2.0,2.0),random(-2.0,2.0),random(-2.0,2.0) })));


		//construct a test light
		_lights.push_back(std::make_shared<PointLight>(PointLight(
			/*color*/ Colors::White,
			/*location*/ VD{ -5.0,-10.0,-15.0 })));
	}


	inline void SceneMultiSpheres::ProceedTime()
	{
		static Uint32 time = 0;
		static VD startLocation{ -5.0,-10.0,-15.0 };

		double angle = time * Scalars::TO_RADS;
		VD lightLocation = startLocation.RotateAround(VDs::Uz, angle);
		_lights[0]->_location = lightLocation;
		time+=10; if (time == 360) time = 0;
	}

}
