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
		_camera.SetPosition(VD{ 0.0, -10.0, 0.0 });
		_camera.SetLookAt(VD{ 0.0, 0.0, 0.0 });
		_camera.SetUp(VD{ 0.0, 0.0, 1.0 });
		_camera.SetHorizontalSize(0.25);
		_camera.SetAspectRatio(1280.0 / 720.0);
		_camera.UpdateCameraGeometry();

		//construct a test sphere
		_objects.push_back(std::make_shared<Sphere>(Sphere()));

		_objects[0]->_baseColor = VD{ 64.0, 128.0, 200.0 };

		//construct a test light
		_lights.push_back(std::make_shared<PointLight>(PointLight()));
		//X positive is towards left, Y positive is towards front (to the reader)
		//Z positive is up (towards top)
		_lights[0]->_location = VD{5.0,-10.0,-5.0}; //VD{ 0.0,0.0,10.0 };//
		_lights[0]->_color = VD{255.0,255.0,255.0};
		_lights[0]->_intensity = 1.0;
	}
}


#endif