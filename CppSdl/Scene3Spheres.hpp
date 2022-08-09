#ifndef SCENE3SPHERES_H
#define SCENE3SPHERES_H

#include "Scene.hpp"

namespace GL::Examples
{

	class Scene3Spheres : public Scene
	{
	public:
		//only inline is accepted and separate cpp definition.
		//if the definition is below then it is not accepted
		Scene3Spheres();
	};
	//static int iCall = 0;

	//inline is obligatory or else "duplicate definitions" will be reported by the compiler
	inline Scene3Spheres::Scene3Spheres()
	{
		//configure the camera
		_camera.SetPosition(VD{ 0.0, -10.0, 0.0 });
		_camera.SetLookAt(VD{ 0.0, 0.0, 0.0 });
		_camera.SetUp(VD{ 0.0, 0.0, 1.0 });
		_camera.SetHorizontalSize(0.25);
		_camera.SetAspectRatio(1280.0 / 720.0);
		_camera.UpdateCameraGeometry();

		_objects.push_back(std::make_shared<Sphere>(Sphere(
			/*basecolor*/ VD{ 64.0, 128.0, 200.0 },
			Transform(/*translation*/VD{ -1.5,0.0,0.0 },	/*rotation*/VDs::Zero,	/*scale*/	VD{ 0.5,0.5,0.75 }
		))));
		_objects.push_back(std::make_shared<Sphere>(Sphere(
			/*basecolor*/ VD{ 255.0, 128.0, 0.0 },
			Transform(/*translation*/ VDs::Zero, /*rotation*/ VDs::Zero, /*scale*/ VD{ 0.75, 0.5, 0.5 }
		))));
		//_objects.push_back(std::make_shared<Sphere>(Sphere(
		//	/*basecolor*/ VD{ 255.0, 200.0, 0.0 },
		//	Transform(/*translation*/ VD{ 1.5,0.0,0.0 }, /*rotation*/ VDs::Zero, /*scale*/ VD{ 0.75,0.75,0.75 }
		//))));
		_objects.push_back(std::make_shared<Sphere>(Sphere(
			/*basecolor*/ VD{ 255.0, 200.0, 0.0 },
			Transform(/*translation*/ VD{ 1.5,0.0,0.0}, /*rotation*/ VDs::Zero, /*scale*/ VD{0.75,0.75,0.75}
		))));

		//construct a test light
		_lights.push_back(std::make_shared<PointLight>(PointLight()));
		//X positive is towards left, Y positive is towards front (to the reader)
		//Z positive is up (towards top)
		_lights[0]->_location = VD{ 5.0,-10.0,-5.0 };
		_lights[0]->_color = VD{ 255.0,255.0,255.0 };
		_lights[0]->_intensity = 1.0;
	}

}

#endif