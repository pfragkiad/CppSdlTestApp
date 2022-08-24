#pragma once

#include "Scene.hpp"
#include "Colors.h"
#include <SDL.h> //MI_P

namespace GL::Examples
{

	class Scene3Spheres : public Scene
	{
	public:
		//only inline is accepted and separate cpp definition.
		//if the definition is below then it is not accepted
		Scene3Spheres();

		void ProceedTime() override;
	};
	//static int iCall = 0;

	//inline is obligatory or else "duplicate definitions" will be reported by the compiler
	inline Scene3Spheres::Scene3Spheres()
	{
		//configure the camera
		_camera.SetProjectionScreen(/*cameraLength*/ 1.0,/*horizontalSize*/ 1.0, /*aspect ratio*/ 1280.0 / 720.0);
		_camera.SetCamera(/*position*/ VD{ 0.0, -10.0, 0.0 }, /*look at*/ VD{ 0.0, 0.0, 0.0 }, /*up vector*/ VD{ 0.0, 0.0, 1.0 });

		_objects.push_back(std::make_shared<Sphere>(Sphere(
			/*basecolor*/ VD{ 64.0, 128.0, 200.0 },
			Transform(
				/*translation*/VD{ -1.5,0.0,2.0 },
				/*rotation*/VD{ 0.0,-Scalars::PI_4,0.0 },
				/*scale*/	VD{ 0.5,0.5,0.75 }
		))));
		_objects.push_back(std::make_shared<Sphere>(Sphere(
			/*basecolor*/ VD{ 255.0, 128.0, 0.0 },
			Transform(
				/*translation*/ VD{ 0.0,0.0,0.0 },
				/*rotation*/ VDs::Zero,
				/*scale*/ VD{ 0.75, 0.5, 0.5 }
		))));
		_objects.push_back(std::make_shared<Sphere>(Sphere(
			/*radius*/ 0.5,
			/*basecolor*/ VD{ 255.0, 200.0, 0.0 },
			/*Translation*/ VD{ 1.5,0.0,0.0 })));

		//construct a test light
		_lights.push_back(std::make_shared<PointLight>(PointLight(
			/*color*/ Colors::White,
			/*location*/ VD{ -5.0,-10.0,15.0 })));
	}

	inline void Scene3Spheres::ProceedTime()
	{
		static Uint32 time = 0;
		double angle = time * Scalars::TO_RADS;

		_objects[0]->SetTransformMatrix(
			Transform(
				/*translation*/VD{ -1.5,0.0,2.0 * cos(angle) },
				/*rotation*/VD{ 0.0,angle,0.0 },
				/*scale*/	VD{ 0.5,0.5,0.75}
		));

		time += 5; if (time == 360) time = 0;
	}
}

