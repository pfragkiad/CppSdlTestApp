#include "../Algebra/Algebra.h"

#include "Window.hpp"

#include "Examples.hpp"

#include <iostream>

using namespace GL;

void testCamera()
{
	Camera testCamera;
	testCamera.SetPosition(VDs::Zero);
	testCamera.SetLookAt(2.0 * VDs::Ux);
	testCamera.SetUp(VDs::Uz);
	testCamera.SetLength(1.0);
	testCamera.SetHorizontalSize(1.0);
	testCamera.SetAspectRatio(1.0);
	testCamera.UpdateCameraGeometry();

	//get the screen center and U, V vectors and display
	VD screenCenter = testCamera.GetScreenCenter();
	VD screenU = testCamera.GetU();
	VD screenV = testCamera.GetV();
	std::cout
		<< "Center:\n" << screenCenter
		<< "\nU:\n" << screenU << "\nV:\n" << screenV;
}

void testUx()
{
	VD ux = VDs::Ux;
	ux[0] = 2.0; //works without changing the original!
	std::cout << ux << std::endl;
}

void testLoops()
{
	for (size_t i = 5; i != numeric_limits<size_t>::max(); i--)
		std::cout << i << endl;

	size_t i = 5; do
	{
		std::cout << i << endl;
	} while (i-- != 0);
}

void testTransforms()
{
	std::cout << "HOMOGENEOUS TESTS\n";
	VD v1 = VD{ 10, -2, -8 };
	VD vh = VDs::ToHomogeneous(v1); //ok
	std::cout << "Original v1:\n" << v1 << std::endl;
	std::cout << "Homogeneous vh:\n" << vh << std::endl;
	std::cout << "Original (back):\n" << VDs::FromHomogeneous(vh) << std::endl; //ok

	std::cout << "TRANSLATE TESTS\n";
	//https://www.brainvoyager.com/bv/doc/UsersGuide/CoordsAndTransforms/SpatialTransformationMatrices.html#:~:text=The%204%20by%204%20transformation,in%20the%20first%20three%20columns.
	MD t = MDs::GetTranslation(VD({ 1,2,3 })); //ok
	std::cout << "Translation:\n" << t << std::endl;


	std::cout << "SCALE TESTS\n";
	t = MDs::GetScale(VD({ 10,20,30 })); //ok
	std::cout << "Scale:\n" << t << std::endl;
	std::cout << "Scaled v1:\n" << MDs::TransformVD(t, v1, false) << endl;

	std::cout << "ROT X TESTS\n";
	t = MDs::GetRotationX(M_PI / 2.0); //tested
	VD v{ {1,1,0} };
	VD vr1 = MDs::TransformVD(t, v, false);//=> should be (1,0,1)
	VD vr2 = MDs::TransformVD(t, vr1, false);//=> should be (1,-1,0)
	std::cout << "(X) Rotated once:\n" << vr1 << std::endl;
	std::cout << "(X) Rotated twice:\n" << vr2 << std::endl;
	std::cout << "ROT X TESTS (VECTOR)\n";
	vr1 = v.RotateAround(VDs::Ux,M_PI/2.0);
	vr2 = vr1.RotateAround(VDs::Ux,M_PI/2.0);
	std::cout << "(X) Rotated once:\n" << vr1 << std::endl;
	std::cout << "(X) Rotated twice:\n" << vr2 << std::endl;

	std::cout << "ROT Y TESTS\n";
	t = MDs::GetRotationY(M_PI / 2.0); //tested
	v = VD{ {0,1,1} };
	vr1 = MDs::TransformVD(t, v, false);//=> (1,1,0)
	vr2 = MDs::TransformVD(t, vr1, false);//=> (0,1,-1)
	std::cout << "(Y) Rotated once:\n" << vr1 << std::endl;
	std::cout << "(Y) Rotated twice:\n" << vr2 << std::endl;
	std::cout << "ROT Y TESTS (VECTOR)\n";
	vr1 = v.RotateAround(VDs::Uy, M_PI / 2.0);
	vr2 = vr1.RotateAround(VDs::Uy, M_PI / 2.0);
	std::cout << "(Y) Rotated once:\n" << vr1 << std::endl;
	std::cout << "(Y) Rotated twice:\n" << vr2 << std::endl;

	std::cout << "ROT Z TESTS\n";
	t = MDs::GetRotationZ(M_PI / 2.0); //tested
	v = VD{ {0,1,1} };
	vr1 = MDs::TransformVD(t, v, false);//=> (-1,0,1)
	vr2 = MDs::TransformVD(t, vr1, false);//=> (0,-1,1)
	std::cout << "(Z) Rotated once:\n" << vr1 << std::endl;
	std::cout << "(Z) Rotated twice:\n" << vr2 << std::endl;
	std::cout << "ROT Z TESTS (VECTOR)\n";
	vr1 = v.RotateAround(VDs::Uz, M_PI / 2.0);
	vr2 = vr1.RotateAround(VDs::Uz, M_PI / 2.0);
	std::cout << "(Z) Rotated once:\n" << vr1 << std::endl;
	std::cout << "(Z) Rotated twice:\n" << vr2 << std::endl;

	exit(0);
}

int main(int argc, char** argv)
{
	//testTransforms();
	//testCamera();
	//testUx();

	GL::Window app{ Examples::Scene3Spheres() };
	//GL::Window app{ Examples::SceneSphere() };
	return app.Run(true);
}

