#ifndef PCA_H
#define PCA_H

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <algorithm>

#include "Matrix.h"
#include "Vector.h"
#include "EIG.h"

// Define error codes.
const int PCA_MATRIXNOTSQUARE = -1;
const int PCA_MATRIXNOTSYMMETRIC = -2;

namespace PCA
{

// Function to compute the column means.
template <typename T>
std::vector<T> ComputeColumnMeans(const Matrix<T> &inputData)
{
	// Determine the size of the input data.
	size_t numRows = inputData.RowsCount();
	size_t numCols = inputData.ColsCount();
	
	// Create a vector for output.
	std::vector<T> output;	
	
	// Loop through and compute means.
	for (size_t j=0; j<numCols; ++j)
	{
		T cumulativeSum = static_cast<T>(0.0);
		for (size_t i=0; i<numRows; ++i)
			cumulativeSum += inputData.Get(i,j);
			
		output.push_back(cumulativeSum / static_cast<T>(numRows));
	}
	
	return output;
}

// Function to subtract the column means.
template <typename T>
void SubtractColumnMeans(Matrix<T> &inputData, std::vector<T> &columnMeans)
{
	// Determine the size of the input data.
	size_t numRows = inputData.RowsCount();
	size_t numCols = inputData.ColsCount();
	
	// Loop through and subtract the means.
	for (size_t j=0; j<numCols; ++j)
	{
		for (size_t i=0; i<numRows; ++i)
			inputData.Set(i,j, inputData.Get(i,j) - columnMeans.at(j));
	}	
}

// Function to compute the covaraince matrix.
template <typename T>
Matrix<T> ComputeCovariance(const Matrix<T> &X)
{
	/* Compute the covariance matrix.
		Note that here we use X'X, rather than XX' as is the usual case.
		This is because we are requiring our data to be arranged with one 
		column (p) for each variable, with one row (k) for each observation. If
		we computed XX', the result would be a [k x k] matrix. The covariance
		matrix should be [p x p], so we need to transpose, hence the use of
		X'X. */
	size_t numRows = X.RowsCount();
	Matrix<T> covX = (static_cast<T>(1.0) / static_cast<T>(numRows - 1)) * (X.Transpose() * X);
	return covX;
}

// Function to compute the eigenvectors of the covariance matrix.
template <typename T>
int ComputeEigenvectors(const Matrix<T> &covarianceMatrix, Matrix<T> &eigenvectors)
{
	// Copy the input matrix.
	Matrix<T> X = covarianceMatrix;

	// The covariance matrix must be square and symmetric.
	if (!X.IsSquare())
		return PCA_MATRIXNOTSQUARE;
		
	// Verify that the matrix is symmetric.
	if (!X.IsSymmetric())
		return PCA_MATRIXNOTSYMMETRIC;
		
	// Compute the eignvalues.
	std::vector<T> eigenValues;
	int returnStatus = EigQR(X, eigenValues);

	// Sort the eigenvalues.
	std::sort(eigenValues.begin(), eigenValues.end());
	std::reverse(eigenValues.begin(), eigenValues.end());

	// Compute the eigenvector for each eigenvalue.
	Vector<T> eV(X.ColsCount());
	Matrix<T> eVM(X.RowsCount(), X.ColsCount());
	for (int j=0; j<eigenValues.size(); ++j)
	{
		T eig = eigenValues.at(j);
		int returnStatus2 = InvPIt<T>(X, eig, eV);
		for (int i=0; i<eV.Count(); ++i)
			eVM.Set(i, j, eV.Get(i));
	}
	
	// Return the eigenvectors.
	eigenvectors = eVM;

	// Return the final return status.	
	return returnStatus;
}

/* Function to compute the principal components of the supplied data. */
template <typename T>
int PCA(const Matrix<T> &inputData, Matrix<T> &outputComponents)
{
	// Make a copy of the input matrix.
	Matrix<T> X = inputData;
	
	// Compute the mean of each column of X.
	std::vector<T> columnMeans = ComputeColumnMeans(X);
	
	// Subtract the column means from the data.
	SubtractColumnMeans<T>(X, columnMeans);
	
	// Compute the covariance matrix.
	Matrix<T> covX = ComputeCovariance(X);
	
	// Compute the eigenvectors.
	Matrix<T> eigenvectors;
	int returnStatus = ComputeEigenvectors(covX, eigenvectors);
	
	// Return the output.
	outputComponents = eigenvectors;
	
	return returnStatus;
}

}

#endif
