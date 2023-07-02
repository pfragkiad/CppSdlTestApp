#ifndef LSQ_H
#define LSQ_H



#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include "Vector.h"
#include "Matrix.h"

// Define error codes.
const int LSQ_NOINVERSE = -1;
const int LSQ_OK = 1;

// The LSQ function.
template <typename T>
int LSQ(const Matrix<T> &Xin, const Vector<T> &yin, Vector<T> &result)
{
	// Firstly, make a copy of X and y.
	Matrix<T> X = Xin;
	Vector<T> y = yin;
	
	// Compute the tranpose of X.
	Matrix<T> XT = X.Transpose();
	
	// Compute XTX.
	Matrix<T> XTX = XT * X;
	
	// Compute the inverse of this.
	if (!XTX.Inverse())
	{
		// We were unable to compute the inverse.
		return LSQ_NOINVERSE;
	}
	
	// Multiply the inverse by XT.
	Matrix<T> XTXXT = XTX * XT;
	
	// And multiply by y to get the final result.
	result = XTXXT * y;
	
	return LSQ_OK;
}

#endif
