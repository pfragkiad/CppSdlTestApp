#pragma once

#include "Scene.hpp"
#include "Colors.h"

namespace GL::Examples
{
	class SceneSphere : public Scene
	{
	public:
		SceneSphere();
	};

	inline GL::Examples::SceneSphere::SceneSphere()
	{
		//configure the camera
		_camera.SetProjectionScreen(/*cameraLength*/ 1.0,/*horizontalSize*/ 1.0, /*aspect ratio*/ 1280.0 / 720.0);
		_camera.SetCamera(/*position*/ VD{ 0.0, 0.0, 10.0 }, /*look at*/ VD{ 0.0, 0.0, 0.0 }, /*up vector*/ VD{ 0.0, 1.0, 0.0 });

		//construct a test sphere
		_objects.push_back(std::make_shared<Sphere>(Sphere()));

		_objects[0]->_baseColor = VD{ 64.0, 128.0, 200.0 };
		//_objects[0]->SetTransformMatrix(
		//	Transform(VD{0.0,0.0,-0.5},VDs::Zero,VDs::One));

		//construct a test light
			//construct a test light
		_lights.push_back(std::make_shared<PointLight>(PointLight(
			/*color*/ Colors::White,
			/*location*/ VD{ -5.0,-10.0,15.0 })));
	}
}

