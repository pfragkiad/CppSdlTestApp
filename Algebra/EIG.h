#ifndef EIG_H
#define EIG_H

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

#include <random> //mt19937, random_device

#include "Matrix.h"
#include "Vector.h"
#include "QR.h"

// Define error codes.
constexpr int EIG_MATRIXNOTSQUARE = -1;
constexpr int EIG_MAXITERATIONSEXCEEDED = -2;
constexpr int EIG_MATRIXNOTSYMMETRIC = -3;

// Function to estimate (real) eigenvalues using QR decomposition.
/* Note that this is only valid for matrices that have ALL real
	eigenvalues. The only matrices that are guaranteed to have only
	real eigenvalues are symmetric matrices. Therefore, this function
	is only guaranteed to work with symmetric matrices. */
template <typename T>
int EigQR(const Matrix<T>& inputMatrix, std::vector<T>& eigenValues)
{
	// Make a copy of the input matrix.
	Matrix<T> A = inputMatrix;

	// Verify that the input matrix is square.
	if (!A.IsSquare())
		return EIG_MATRIXNOTSQUARE;

	// Verify that the matrix is symmetric.
	if (!A.IsSymmetric())
		return EIG_MATRIXNOTSYMMETRIC;

	// The number of eigenvalues is equal to the number of rows.
	size_t numRows = A.RowsCount();

	// Create an identity matrix of the same dimensions.
	Matrix<T> identityMatrix(numRows, numRows);
	identityMatrix.SetToIdentity();

	// Create matrices to store Q and R.
	Matrix<T> Q(numRows, numRows);
	Matrix<T> R(numRows, numRows);

	// Loop through each iteration.
	size_t maxIterations = 10000;
	size_t iterationCount = 0;
	bool continueFlag = true;
	while ((iterationCount < maxIterations) && continueFlag)
	{
		// Compute the QR decomposition of A.
		int returnValue = QR<T>(A, Q, R);

		// Compute the next value of A as the product of R and Q.
		A = R * Q;

		/* Check if A is now close enough to being upper-triangular.
			We can do this using the IsRowEchelon() function from the
			Matrix class. */
		if (A.IsRowEchelon())
			continueFlag = false;

		// Increment iterationCount.
		iterationCount++;
	}

	// At this point, the eigenvalues should be the diagonal elements of A.
	for (int i = 0; i < numRows; ++i)
		eigenValues.push_back(A.Get(i, i));

	// Set the return status accordingly.
	if (iterationCount == maxIterations)
		return EIG_MAXITERATIONSEXCEEDED;
	else
		return 0;

}

// Function to perform inverse power iteration method.
template <typename T>
int InvPIt(const Matrix<T>& inputMatrix, const T& eigenValue, Vector<T>& eigenVector)
{
	// Make a copy of the input matrix.
	Matrix<T> A = inputMatrix;

	// Verify that the input matrix is square.
	if (!A.IsSquare())
		return EIG_MATRIXNOTSQUARE;

	// Setup a random number generator.
	std::random_device myRandomDevice;
	std::mt19937 myRandomGenerator(myRandomDevice());
	std::uniform_int_distribution<int> myDistribution(1, 10);

	/* The number of eigenvectors and eigenvalues that we will compute will be
		equal to the number of rows in the input matrix. */
	size_t numRows = A.RowsCount();

	// Create an identity matrix of the same dimensions.
	Matrix<T> identityMatrix(numRows, numRows);
	identityMatrix.SetToIdentity();

	// Create an initial vector, v.
	Vector<T> v(numRows);
	for (size_t i = 0; i < numRows; ++i)
		v.Set(i, static_cast<T>(myDistribution(myRandomGenerator)));

	// Iterate.
	int maxIterations = 100;
	int iterationCount = 0;
	T deltaThreshold = static_cast<T>(1e-9);
	T delta = static_cast<T>(1e6);
	Vector<T> prevVector(numRows);
	Matrix<T> tempMatrix(numRows, numRows);

	while ((iterationCount < maxIterations) && (delta > deltaThreshold))
	{
		// Store a copy of the current working vector to use for computing delta.
		prevVector = v;

		// Compute the next value of v.
		tempMatrix = A - (eigenValue * identityMatrix);
		tempMatrix.Inverse();
		v = tempMatrix * v;
		v.Normalize();

		// Compute delta.
		delta = (v - prevVector).Length();

		// Increment iteration count.
		iterationCount++;
	}

	// Return the estimated eigenvector.
	eigenVector = v;

	// Set the return status accordingly.
	if (iterationCount == maxIterations)
		return EIG_MAXITERATIONSEXCEEDED;

	return 0;
}

// The EIG function (power iteration method).
template <typename T>
int EigPIt(const Matrix<T>& X, T& eigenValue, Vector<T>& eigenVector)
{
	// Make a copy of the input matrix.
	Matrix<T> inputMatrix = X;

	// Verify that the input matrix is square.
	if (!inputMatrix.IsSquare())
		return EIG_MATRIXNOTSQUARE;

	// Setup a random number generator.
	std::random_device myRandomDevice;
	std::mt19937 myRandomGenerator(myRandomDevice());
	std::uniform_int_distribution<int> myDistribution(1, 10);

	/* The number of eigenvectors and eigenvalues that we will compute will be
		equal to the number of rows in the input matrix. */
	size_t numRows = inputMatrix.RowsCount();

	// Create an identity matrix of the same dimensions.
	Matrix<T> identityMatrix(numRows, numRows);
	identityMatrix.SetToIdentity();

	/* **************************************************************
		Compute the eigenvector.
	************************************************************** */

	// Create an initial vector, v.
	Vector<T> v(numRows);
	for (size_t i = 0; i < numRows; ++i)
		v.Set(i, static_cast<T>(myDistribution(myRandomGenerator)));

	// Loop over the required number of iterations.
	Vector<T> v1(numRows);
	size_t numIterations = 1000;
	for (size_t i = 0; i < numIterations; ++i)
	{
		v1 = inputMatrix * v;
		v1.Normalize();
		v = v1;
	}

	// Store this eigenvector.
	eigenVector = v1;

	/* **************************************************************
		Compute the eigenvalue corresponding to this eigenvector.
	************************************************************** */

	// Compute the cumulative sum.
	T cumulativeSum = static_cast<T>(0.0);
	for (size_t i = 1; i < numRows; ++i)
		cumulativeSum += inputMatrix.Get(0, i) * v1.Get(i);

	eigenValue = (cumulativeSum / v1.Get(0)) + inputMatrix.Get(0, 0);

	return 0;
}

#endif
