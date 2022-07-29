#ifndef QR_H
#define QR_H

/* *************************************************************************************************

	qbQR

	Function to perform QR decomposition on a given input matrix.

	*** INPUTS ***

	A					Matrix<T>	The matrix on which to perform QR decomposition.
	Q					Matrix<T>	The output Q matrix.
	R					Matrix<T>	The output R matrix.

	*** OUTPUTS ***

	INT				Flag indicating success or failure of the process.
						1 Indicates success.
						-1 indicates failure due to a non-square input matrix.

	Uses an implementation of Householder reflections to perform QR decomposition.

	Created as part of the qbLinAlg linear algebra library, which is intended to be primarily for
	educational purposes. For more details, see the corresponding videos on the QuantitativeBytes
	YouTube channel at:

	www.youtube.com/c/QuantitativeBytes

	************************************************************************************************* */

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
	int numCols = inputMatrix.GetNumCols();

	// Create a vector to store the P matrices for each column.
	std::vector<Matrix<T>> Plist;

	// Loop through each column.
	for (int j = 0; j < numCols - 1; ++j)
	{
		// Create the a1 and b1 vectors.
		// a1 is the column vector from A.
		// b1 is the vector onto which we wish to reflect a1.
		Vector<T> a1(numCols - j);
		Vector<T> b1(numCols - j);
		for (int i = j; i < numCols; ++i)
		{
			a1.SetElement(i - j, inputMatrix.GetElement(i, j));
			b1.SetElement(i - j, static_cast<T>(0.0));
		}
		b1.SetElement(0, static_cast<T>(1.0));

		// Compute the norm of the a1 vector.
		T a1norm = a1.norm();

		// Compute the sign we will use.
		int sgn = -1;
		if (a1.GetElement(0) < static_cast<T>(0.0))
			sgn = 1;

		// Compute the u-vector.
		Vector<T> u = a1 - (sgn * a1norm * b1);

		// Compute the n-vector.
		Vector<T> n = u.Normalized();

		// Convert n to a matrix so that we can transpose it.
		Matrix<T> nMat(numCols - j, 1);
		for (int i = 0; i < (numCols - j); ++i)
			nMat.SetElement(i, 0, n.GetElement(i));

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
		for (int row = j; row < numCols; ++row)
		{
			for (int col = j; col < numCols; ++col)
			{
				P.SetElement(row, col, Ptemp.GetElement(row - j, col - j));
			}
		}

		// Store the result into the Plist vector.
		Plist.push_back(P);

		// Apply this transform matrix to inputMatrix and use this result
		// next time through the loop.
		inputMatrix = P * inputMatrix;
	}

	// Compute Q.
	Matrix<T> Qmat = Plist.at(0);
	for (int i = 1; i < (numCols - 1); ++i)
	{
		Qmat = Qmat * Plist.at(i).Transpose();
	}

	// Return the Q matrix.
	Q = Qmat;

	// Compute R.
	int numElements = Plist.size();
	Matrix<T> Rmat = Plist.at(numElements - 1);
	for (int i = (numElements - 2); i >= 0; --i)
	{
		Rmat = Rmat * Plist.at(i);
	}
	Rmat = Rmat * A;

	// And return the R matrix.
	R = Rmat;

	return QR_OK;
}

#endif
