#ifndef QR_H
#define QR_H



#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

#include "Matrix.h"
#include "Vector.h"

	// Define error codes.
const int QR_MATRIXNOTSQUARE = -1;
const int QR_OK = 0;

// The qbQR function.
template <typename T>
int QR(const Matrix<T>& A, Matrix<T>& Q, Matrix<T>& R)
{

	// Make a copy of the input matrix.
	Matrix<T> inputMatrix = A;

	// Verify that the input matrix is square.
	if (!inputMatrix.IsSquare())
		return QR_MATRIXNOTSQUARE;

	// Determine the number of columns (and rows, since the matrix is square).
	size_t numCols = inputMatrix.ColsCount();

	// Create a vector to store the P matrices for each column.
	std::vector<Matrix<T>> Plist;

	// Loop through each column.
	for (size_t j = 0; j < numCols - 1; ++j)
	{
		// Create the a1 and b1 vectors.
		// a1 is the column vector from A.
		// b1 is the vector onto which we wish to reflect a1.
		Vector<T> a1(numCols - j);
		Vector<T> b1(numCols - j);
		for (size_t i = j; i < numCols; ++i)
		{
			a1.Set(i - j, inputMatrix.Get(i, j));
			b1.Set(i - j, static_cast<T>(0.0));
		}
		b1.Set(0, static_cast<T>(1.0));

		// Compute the norm of the a1 vector.
		T a1norm = a1.Length();

		// Compute the sign we will use.
		int	sgn = a1.Get(0) < static_cast<T>(0.0)? 1 : -1;

		// Compute the u-vector.
		Vector<T> u = a1 - sgn * a1norm * b1;

		// Compute the n-vector.
		Vector<T> n = !u;

		// Convert n to a matrix so that we can transpose it.
		Matrix<T> nMat(numCols - j, 1);
		for (size_t i = 0; i < numCols - j; ++i)
			nMat.Set(i, 0, n.Get(i));

		// Transpose nMat.
		Matrix<T> nMatT = nMat.Transpose();

		// Create an identity matrix of the appropriate size.
		Matrix<T> I(numCols - j, numCols - j);
		I.SetToIdentity();

		// Compute Ptemp.
		Matrix<T> Ptemp = I - static_cast<T>(2.0) * nMat * nMatT;

		// Form the P matrix with the original dimensions.
		Matrix<T> P(numCols, numCols);
		P.SetToIdentity();
		for (size_t row = j; row < numCols; ++row)
			for (size_t col = j; col < numCols; ++col)
				P.Set(row, col, Ptemp.Get(row - j, col - j));

		// Store the result into the Plist vector.
		Plist.push_back(P);

		// Apply this transform matrix to inputMatrix and use this result
		// next time through the loop.
		inputMatrix = P * inputMatrix;
	}

	// Compute Q.
	Matrix<T> Qmat = Plist[0];
	for (size_t i = 1; i < numCols - 1; ++i)
	{
		Qmat = Qmat * Plist[i].Transpose();
	}

	// Return the Q matrix.
	Q = Qmat;

	// Compute R.
	size_t numElements = Plist.size();
	Matrix<T> Rmat = Plist[numElements - 1];
	for (size_t i = numElements - 1; i-- > 0;) //starts from numElements-2
		Rmat  *= Plist[i];
	
	Rmat = Rmat * A;

	// And return the R matrix.
	R = Rmat;

	return QR_OK;
}

#endif
