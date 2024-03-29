#ifndef LINSOLVE_H
#define LINSOLVE_H



#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

#include "Matrix.h"
#include "Vector.h"

	// Define error codes.
const int LINSOLVE_NOUNIQUESOLUTION = -1;
const int LINSOLVE_NOSOLUTIONS = -2;
const int LINSOLVE_OK = 1;

// The qbLinSolve function.
template <typename T>
int LinSolve(const Matrix<T>& aMatrix, const Vector<T>& bVector, Vector<T>& resultVec)
{
	// Make a copy of the input matrix, aMatrix.
	// We will use this to create the augmented matrix, so we have
	// to make a copy.
	Matrix<T> inputMatrix = aMatrix;

	// Compute the rank of the original matrix.
	size_t originalRank = inputMatrix.Rank();

	/* Combine inputMatrix and bVector together into a single matrix,
		ready for using Gaussian elimination to reduce to
		row-echelon form. */

		// Extract data from bVector.
	size_t numDims = bVector.Count();
	std::vector<T> bVecData;
	for (size_t i = 0; i < numDims; ++i)
		bVecData.push_back(bVector.Get(i));

	// Use this to create a Matrix object with the same data (nx1).
	Matrix<T> bMatrix(numDims, 1, bVecData);

	// Combine the two matrices together.
	inputMatrix.Join(bMatrix);

	/* Use Gaussian elmination to convert to row-echelon form. */
	Matrix<T> rowEchelonMatrix = inputMatrix.RowEchelon();

	/* Comute the rank of the augmented matrix.
		Note that we do this after performing Gaussian elimination to
		reduce the matrix to row echelon form so that if this was
		successful, there is no need to repeat this operation twice. */
	size_t augmentedRank = rowEchelonMatrix.Rank();

	/* *********************************************************************
		Test the two ranks to determine the nature of the system we
		are dealing with. The conditions are as follows:

		n = number of rows.

		1) originalRank = augmentedRank = n	=> A unique solution exists.
		2) originalRank = augmentedRank < n	=> An infinite number of solutions exist.
		3) originalRank < augmentedRank			=> No solutions exist.
		********************************************************************* */
	if (originalRank == augmentedRank && originalRank < inputMatrix.RowsCount())
		return LINSOLVE_NOUNIQUESOLUTION;

	if (originalRank < augmentedRank)
		return LINSOLVE_NOSOLUTIONS;

	/* Create a Vector object to store the output. Initially we will
		populate this with the data from bVecData, but we are going to modify
		the elements as we compute them. */
	Vector<T> output(bVecData);

	// Now use back-substitution to compute the result.
	size_t numRows = rowEchelonMatrix.RowsCount();
	size_t numCols = rowEchelonMatrix.ColsCount();
	size_t startRow = numRows - 1;

	// Loop over the rows, in reverse order.
	for (size_t i = startRow+1; i-- > 0; ) //starts from startRow
	{
		// Extract the currentResult for this row.
		T currentResult = rowEchelonMatrix.Get(i, numCols - 1);

		// Compute the cumulative sum.
		T cumulativeSum = static_cast<T>(0.0);
		for (size_t j = i + 1; j < numRows; ++j)
			cumulativeSum += (rowEchelonMatrix.Get(i, j) * output.Get(j));

		// Compute the answer.
		T finalAnswer = (currentResult - cumulativeSum) / rowEchelonMatrix.Get(i, i);

		// And store.
		output.Set(i, finalAnswer);
	}

	// Return the output.
	resultVec = output;

	return LINSOLVE_OK;
}

#endif
