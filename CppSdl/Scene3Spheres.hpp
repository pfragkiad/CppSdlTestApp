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

		_objects.push_back(std::make_shared<Sphere>( Sphere(
				/*basecolor*/ VD{ 64.0, 128.0, 200.0 },
				Transform(
					/*translation*/VD{ -1.5,0.0,0.0 },	/*rotation*/Algebra::Zero,	/*scale*/	VD{ 0.5,0.5,0.75 }
		))));
		_objects.push_back(std::make_shared<Sphere>( Sphere(
				/*basecolor*/ VD{ 255.0, 128.0, 0.0 },
				Transform(
					/*translation*/ Algebra::Zero, /*rotation*/ Algebra::Zero, /*scale*/ VD{ 0.75, 0.5, 0.5 }
		))));
		_objects.push_back(std::make_shared<Sphere>(Sphere(
			/*basecolor*/ VD{ 255.0, 200.0, 0.0 },
			Transform(
				/*translation*/ VD{ 1.5,0.0,0.0 }, /*rotation*/ Algebra::Zero, /*scale*/ VD{ 0.75,0.75,0.75 }
		))));


		//_objects.push_back(std::make_shared<Sphere>(Sphere()));
		//_objects.push_back(std::make_shared<Sphere>(Sphere()));
		//_objects.push_back(std::make_shared<Sphere>(Sphere()));

		////modify the spheres
		//Transform m1, m2, m3;
		//m1.Set(VD{ -1.5,0.0,0.0 }, Algebra::Zero, VD{ 0.5,0.5,0.75 });
		//m2.Set(Algebra::Zero, Algebra::Zero, VD{ 0.75,0.5,0.5 });
		//m3.Set(VD{ 1.5,0.0,0.0 }, Algebra::Zero, VD{ 0.75,0.75,0.75 });
		//_objects[0]->SetTransformMatrix(m1);
		//_objects[1]->SetTransformMatrix(m2);
		//_objects[2]->SetTransformMatrix(m3);
		//_objects[0]->_baseColor = VD{ 64.0, 128.0, 200.0 };//VD{ 255.0, 0.0, 0.0 }; 
		//_objects[1]->_baseColor = VD{ 255.0, 128.0, 0.0 };//VD{ 0.0, 255.0, 0.0 };
		//_objects[2]->_baseColor =  VD{ 255.0, 200.0, 0.0 };//VD{ 0.0,0.0,255.0 };



		//construct a test light
		_lights.push_back(std::make_shared<PointLight>(PointLight()));
		//X positive is towards left, Y positive is towards front (to the reader)
		//Z positive is up (towards top)
		_lights.at(0)->_location = VD{ 5.0,-10.0,-5.0 };
		_lights.at(0)->_color = VD{ 255.0,255.0,255.0 };
		_lights.at(0)->_intensity = 1.0;
	}

}

#endif