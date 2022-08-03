#pragma once

#include "Vector.h"


class Vectors
{
public:
	static Vector<double> Zero;
	static Vector<double> UnitX;
	static Vector<double> UnitY;
	static Vector<double> UnitZ;
};

Vector<double> Vectors::Zero{ 0.0,0.0,0.0 };
Vector<double> Vectors::UnitX{ 1.0,0.0,0.0 };
Vector<double> Vectors::UnitY{ 0.0,1.0,0.0 };
Vector<double> Vectors::UnitZ{ 0.0,0.0,1.0 };

