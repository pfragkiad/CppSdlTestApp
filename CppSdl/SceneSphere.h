#ifndef SCENE_SPHERE
#define SCENE_SPHERE

#include "Scene.hpp"

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
		_lights.push_back(std::make_shared<PointLight>(PointLight()));
		//X positive is towards left, Y positive is towards front (to the reader)
		//Z positive is up (towards top)

		// Z seems opposite (positive Z is down)
		// X seems opposite (positive X is left)
		// Y seems ok (positive Y away from reader  M_PI- ...approach)
		_lights[0]->_location = VD{ 5.0,-10.0,-5.0 };//
		_lights[0]->_lightColor = VD{ 255.0,255.0,255.0 };
		_lights[0]->_intensity = 1.0;
	}
}


#endif