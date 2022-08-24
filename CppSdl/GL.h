#pragma once

//#define USE_RGB_VECTORS

#include <vector> //rgb vectors (used by: Scene)
#include <iostream> //diagnostic messages
#include <memory> //safe pointers (used by: LightBase, Scene)
#include <algorithm> //fill array (used by: Image.cpp)

//#include "../Algebra/Algebra.h"
#include <Algebra.h>

#include <SDL.h>

//utilities
#include "Timer.h"
#include "Colors.h"
#include "Random.h"

#include "Image.hpp" //used by: Scene, Window
#include "Ray.hpp" //used by: LightBase, Camera, Shape, Transform
#include "IntersectionInfo.h" //used by: Shape
#include "Transform.hpp" //used by: Shape
#include "Shape.hpp" //used by: LightBase
#include "LightBase.hpp" //used by: PointLight


#include "PointLight.hpp" //used by: Scene
#include "Sphere.hpp" //used by: Scene

#include "Camera.hpp" //used by: Scene, Window
#include "Scene.hpp" //used by: Window
#include "Window.hpp"

#include "Examples.hpp"
