
#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <exception>
#include "Vector.h"
#include <algorithm> //fill

template <class T>
class Matrix
{
public:
	// Define the various constructors.
	Matrix();
	Matrix(size_t nRows, size_t nCols);
	Matrix(size_t nRows, size_t nCols, const T* inputData);
	Matrix(const Matrix<T>& inputMatrix);
	Matrix(size_t nRows, size_t nCols, const std::vector<T>& inputData);

	// And the destructor.
	~Matrix();

	// Configuration methods.
	bool Resize(size_t numRows, size_t numCols);
	void SetToIdentity();

	// Element access methods.
	T Get(size_t row, size_t col) const;
	bool Set(size_t row, size_t col, T elementValue);
	size_t RowsCount() const;
	size_t ColsCount() const;

	// Manipulation methods.
	// Compute matrix inverse.
	bool Inverse();
	// Convert to row echelon form.
	Matrix<T> RowEchelon();
	// Return the transpose.
	Matrix<T> Transpose() const;

	// Compute determinant.
	T Determinant();

	// Overload == operator.
	bool operator== (const Matrix<T>& rhs);
	bool Compare(const Matrix<T>& matrix1, double tolerance);

	// Overload the assignment operator.
	Matrix<T> operator= (const Matrix<T>& rhs);
	//xtra
	Matrix<T> operator*= (const T& rhs);
	Matrix<T> operator*= (const Matrix<T>& rhs);


	// Overload +, - and * operators (friends).
	template <class T> friend Matrix<T> operator+ (const Matrix<T>& lhs, const Matrix<T>& rhs);
	template <class T> friend Matrix<T> operator+ (const T& lhs, const Matrix<T>& rhs);
	template <class T> friend Matrix<T> operator+ (const Matrix<T>& lhs, const T& rhs);

	template <class T> friend Matrix<T> operator- (const Matrix<T>& lhs, const Matrix<T>& rhs);
	template <class T> friend Matrix<T> operator- (const T& lhs, const Matrix<T>& rhs);
	template <class T> friend Matrix<T> operator- (const Matrix<T>& lhs, const T& rhs);

	template <class T> friend Matrix<T> operator* (const Matrix<T>& lhs, const Matrix<T>& rhs);
	template <class T> friend Matrix<T> operator* (const T& lhs, const Matrix<T>& rhs);
	template <class T> friend Matrix<T> operator* (const Matrix<T>& lhs, const T& rhs);

	// Matrix * Vector.
	template <class T> friend Vector<T> operator* (const Matrix<T>& lhs, const Vector<T>& rhs);


	bool Separate(Matrix<T>& matrix1, Matrix<T>& matrix2, size_t colNum);
	bool Join(const Matrix<T>& matrix2);
	Matrix<T> FindSubMatrix(size_t rowNum, size_t colNum);

	// Function to return the rank of the matrix.
	size_t Rank();

	bool IsSquare();
	bool IsRowEchelon();
	bool IsNonZero();
	bool IsSymmetric();
	void Print() const;
	void Print(int precision) const;

	template <class T> friend std::ostream& operator << (std::ostream& os, const Matrix& m);
private:
	size_t Sub2Ind(size_t row, size_t col) const;
	bool CloseEnough(T f1, T f2);
	void SwapRow(size_t i, size_t j);
	void MultAdd(size_t i, size_t j, T multFactor);
	void MultRow(size_t i, T multFactor);
	size_t FindRowWithMaxElement(size_t colNumber, size_t startingRow);

	//fields
	T* _MData;
	size_t _nRows, _nCols, _nElements;
};

//// A simple function to print a matrix to stdout.
//template <class T>
//void PrintMatrix(Matrix<T> matrix)
//{
//	int nRows = matrix.GetNumRows();
//	int nCols = matrix.GetNumCols();
//	for (int row = 0; row < nRows; ++row)
//	{
//		for (int col = 0; col < nCols; ++col)
//		{
//			std::cout << std::fixed << std::setprecision(3) << matrix.GetElement(row, col) << "  ";
//		}
//		std::cout << std::endl;
//	}
//}


template <class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m)
{
	size_t _nRows = m.RowsCount(), _nCols = m.ColsCount();
	for (size_t row = 0; row < _nRows; ++row)
	{
		for (size_t col = 0; col < _nCols; ++col)
			os << std::fixed << std::setprecision(6) << m.Get(row, col) << "  ";
		os << std::endl;
	}
	return os;
}


/* **************************************************************************************************
CONSTRUCTOR / DESTRUCTOR FUNCTIONS
/* *************************************************************************************************/
// The default constructor.
template <class T>
Matrix<T>::Matrix()
{
	_nRows = 1;
	_nCols = 1;
	_nElements = 1;
	_MData = nullptr;
}

// Construct empty matrix (all elements 0)
template <class T>
Matrix<T>::Matrix(size_t nRows, size_t nCols)
{
	_nRows = nRows;
	_nCols = nCols;
	_nElements = _nRows * _nCols;
	_MData = new T[_nElements];
	for (size_t i = 0; i < _nElements; i++)
		_MData[i] = 0.0;
}

// Construct from const linear array.
template <class T>
Matrix<T>::Matrix(size_t nRows, size_t nCols, const T* inputData)
{
	_nRows = nRows;
	_nCols = nCols;
	_nElements = _nRows * _nCols;
	_MData = new T[_nElements];
	for (size_t i = 0; i < _nElements; i++)
		_MData[i] = inputData[i];
}

// The copy constructor.
template <class T>
Matrix<T>::Matrix(const Matrix<T>& inputMatrix)
{
	_nRows = inputMatrix._nRows;
	_nCols = inputMatrix._nCols;
	_nElements = inputMatrix._nElements;

	_MData = new T[_nElements];
	for (size_t i = 0; i < _nElements; i++)
		_MData[i] = inputMatrix._MData[i];
}

// Construct from std::vector.
template <class T>
Matrix<T>::Matrix(size_t nRows, size_t nCols, const std::vector<T>& inputData)
{
	_nRows = nRows;
	_nCols = nCols;
	_nElements = _nRows * _nCols;
	_MData = new T[_nElements];
	for (size_t i = 0; i < _nElements; ++i)
		_MData[i] = inputData.at(i);
}

template <class T>
Matrix<T>::~Matrix()
{
	// Destructor.
	if (_MData)
		delete[] _MData;

	_MData = nullptr;
}

/* **************************************************************************************************
CONFIGURATION FUNCTIONS
/* *************************************************************************************************/
template <class T>
bool Matrix<T>::Resize(size_t numRows, size_t numCols)
{
	_nRows = numRows;
	_nCols = numCols;
	_nElements = _nRows * _nCols;
	delete[] _MData;
	_MData = new T[_nElements];
	if (_MData == nullptr) return false;

	
	std::fill(_MData, _MData + _nElements, static_cast<T>(0.0));
	//for (size_t i = 0; i < _nElements; i++)
	//	_MData[i] = 0.0;

	return true;

}

// Function to convert the existing matrix into an identity matrix.
template <class T>
void Matrix<T>::SetToIdentity()
{
	if (!IsSquare())
		throw std::invalid_argument("Cannot form an identity matrix that is not square.");

	for (size_t row = 0; row < _nRows; ++row)
		for (size_t col = 0; col < _nCols; ++col)
			_MData[Sub2Ind(row, col)] = col == row ? static_cast<T>(1.0) : static_cast<T>(0.0);
}

/* **************************************************************************************************
ELEMENT FUNCTIONS
/* *************************************************************************************************/
template <class T>
T Matrix<T>::Get(size_t row, size_t col) const
{
	size_t linearIndex = Sub2Ind(row, col);
	//if (linearIndex >= 0)
	return _MData[linearIndex];

	//return 0.0;
}

template <class T>
bool Matrix<T>::Set(size_t row, size_t col, T elementValue)
{
	try
	{
		size_t linearIndex = Sub2Ind(row, col);
		//if (linearIndex >= 0)

		_MData[linearIndex] = elementValue;
		return true;

	}
	catch (std::invalid_argument exc) {
		return false;
	}
}

template <class T>
size_t Matrix<T>::RowsCount() const
{
	return _nRows;
}

template <class T>
size_t Matrix<T>::ColsCount() const
{
	return _nCols;
}

template <class T>
bool Matrix<T>::Compare(const Matrix<T>& matrix1, double tolerance)
{
	// First, check that the matrices have the same dimensions.
	size_t numRows1 = matrix1._nRows;
	size_t numCols1 = matrix1._nCols;
	if (numRows1 != _nRows || numCols1 != _nCols)
		return false;

	// Loop over all the elements and compute the sum-of-squared-differences.
	double cumulativeSum = 0.0;
	for (size_t i = 0; i < _nElements; ++i)
	{
		T element1 = matrix1._MData[i];
		T element2 = _MData[i];
		cumulativeSum += ((element1 - element2) * (element1 - element2));
	}
	double finalValue = sqrt(cumulativeSum / ((numRows1 * numCols1) - 1));

	return finalValue < tolerance;
}

/* **************************************************************************************************
OVERLOADED OPERATOR FUNCTIONS
/* *************************************************************************************************/

/* **************************************************************************************************
THE + OPERATOR
/* *************************************************************************************************/
// matrix + matrx.
template <class T>
Matrix<T> operator+ (const Matrix<T>& lhs, const Matrix<T>& rhs)
{
	size_t numRows = lhs._nRows;
	size_t numCols = lhs._nCols;
	size_t numElements = numRows * numCols;
	T* tempResult = new T[numElements];
	for (size_t i = 0; i < numElements; i++)
		tempResult[i] = lhs._MData[i] + rhs._MData[i];

	Matrix<T> result(numRows, numCols, tempResult);
	delete[] tempResult;
	return result;
}

// scaler + matrix
template <class T>
Matrix<T> operator+ (const T& lhs, const Matrix<T>& rhs)
{
	size_t numRows = rhs._nRows;
	size_t numCols = rhs._nCols;
	size_t numElements = numRows * numCols;
	T* tempResult = new T[numElements];
	for (size_t i = 0; i < numElements; ++i)
		tempResult[i] = lhs + rhs._MData[i];

	Matrix<T> result(numRows, numCols, tempResult);
	delete[] tempResult;
	return result;
}

// matrix + scaler
template <class T>
Matrix<T> operator+ (const Matrix<T>& lhs, const T& rhs)
{
	size_t numRows = lhs._nRows;
	size_t numCols = lhs._nCols;
	size_t numElements = numRows * numCols;
	T* tempResult = new T[numElements];
	for (size_t i = 0; i < numElements; ++i)
		tempResult[i] = lhs._MData[i] + rhs;

	Matrix<T> result(numRows, numCols, tempResult);
	delete[] tempResult;
	return result;
}

/* **************************************************************************************************
THE - OPERATOR
/* *************************************************************************************************/
// matrix - matrix
template <class T>
Matrix<T> operator- (const Matrix<T>& lhs, const Matrix<T>& rhs)
{
	size_t numRows = lhs._nRows;
	size_t numCols = lhs._nCols;
	size_t numElements = numRows * numCols;
	T* tempResult = new T[numElements];
	for (size_t i = 0; i < numElements; i++)
		tempResult[i] = lhs._MData[i] - rhs._MData[i];

	Matrix<T> result(numRows, numCols, tempResult);
	delete[] tempResult;
	return result;
}

// scaler - matrix
template <class T>
Matrix<T> operator- (const T& lhs, const Matrix<T>& rhs)
{
	size_t numRows = rhs._nRows;
	size_t numCols = rhs._nCols;
	size_t numElements = numRows * numCols;
	T* tempResult = new T[numElements];
	for (size_t i = 0; i < numElements; ++i)
		tempResult[i] = lhs - rhs._MData[i];

	Matrix<T> result(numRows, numCols, tempResult);
	delete[] tempResult;
	return result;
}

// matrix - scaler
template <class T>
Matrix<T> operator- (const Matrix<T>& lhs, const T& rhs)
{
	size_t numRows = lhs._nRows;
	size_t numCols = lhs._nCols;
	size_t numElements = numRows * numCols;
	T* tempResult = new T[numElements];
	for (size_t i = 0; i < numElements; ++i)
		tempResult[i] = lhs._MData[i] - rhs;

	Matrix<T> result(numRows, numCols, tempResult);
	delete[] tempResult;
	return result;
}

/* **************************************************************************************************
THE * OPERATOR
/* *************************************************************************************************/
// matrix * vector
template <class T>
Vector<T> operator* (const Matrix<T>& lhs, const Vector<T>& rhs)
{
	// Verify the dimensions of the inputs.
	if (lhs._nCols != rhs.Count())
		throw std::invalid_argument("Number of columns in matrix must equal number of rows in vector.");

	// Setup the vector for the output.
	Vector<T> result(lhs._nRows);

	// Loop over rows and columns and perform the multiplication operation element-by-element.
	for (size_t row = 0; row < lhs._nRows; ++row)
	{
		T cumulativeSum = static_cast<T>(0.0);
		for (size_t col = 0; col < lhs._nCols; ++col)
			cumulativeSum += (lhs.Get(row, col) * rhs.Get(col));
		result.Set(row, cumulativeSum);
	}

	return result;
}

// scaler * matrix
template <class T>
Matrix<T> operator* (const T& lhs, const Matrix<T>& rhs)
{
	size_t numRows = rhs._nRows;
	size_t numCols = rhs._nCols;
	size_t numElements = numRows * numCols;
	T* tempResult = new T[numElements];
	for (size_t i = 0; i < numElements; ++i)
		tempResult[i] = lhs * rhs._MData[i];

	Matrix<T> result(numRows, numCols, tempResult);
	delete[] tempResult;
	return result;
}

// matrix * scaler
template <class T>
Matrix<T> operator* (const Matrix<T>& lhs, const T& rhs)
{
	size_t numRows = lhs._nRows;
	size_t numCols = lhs._nCols;
	size_t numElements = numRows * numCols;
	T* tempResult = new T[numElements];
	for (size_t i = 0; i < numElements; ++i)
		tempResult[i] = lhs._MData[i] * rhs;

	Matrix<T> result(numRows, numCols, tempResult);
	delete[] tempResult;
	return result;
}

// matrix * matrix
template <class T>
Matrix<T> operator* (const Matrix<T>& lhs, const Matrix<T>& rhs)
{
	size_t r_numRows = rhs._nRows;
	size_t r_numCols = rhs._nCols;
	size_t l_numRows = lhs._nRows;
	size_t l_numCols = lhs._nCols;

	if (l_numCols == r_numRows)
	{
		// This is the standard matrix multiplication condition.
		// The output will be the same size as the RHS.
		T* tempResult = new T[lhs._nRows * rhs._nCols];

		// Loop through each row of the LHS.
		for (size_t lhsRow = 0; lhsRow < l_numRows; lhsRow++)
		{
			// Loop through each column on the RHS.
			for (size_t rhsCol = 0; rhsCol < r_numCols; rhsCol++)
			{
				T elementResult = static_cast<T>(0.0);
				// Loop through each element of this LHS row.
				for (size_t lhsCol = 0; lhsCol < l_numCols; lhsCol++)
				{
					// Compute the LHS linear index.
					size_t lhsLinearIndex = (lhsRow * l_numCols) + lhsCol;

					// Compute the RHS linear index (based on LHS col).
					// rhs row number equal to lhs column number.
					size_t rhsLinearIndex = (lhsCol * r_numCols) + rhsCol;

					// Perform the calculation on these elements.
					elementResult += (lhs._MData[lhsLinearIndex] * rhs._MData[rhsLinearIndex]);
				}

				// Store the result.
				size_t resultLinearIndex = (lhsRow * r_numCols) + rhsCol;
				tempResult[resultLinearIndex] = elementResult;
			}
		}
		Matrix<T> result(l_numRows, r_numCols, tempResult);
		delete[] tempResult;
		return result;
	}
	else
	{
		Matrix<T> result(1, 1);
		return result;
	}
}

/* **************************************************************************************************
THE == OPERATOR
/* *************************************************************************************************/
template <class T>
bool Matrix<T>::operator== (const Matrix<T>& rhs)
{
	// Check if the matricies are the same size, if not return false.
	if (this->_nRows != rhs._nRows && this->_nCols != rhs._nCols)
		return false;

	// Check if the elements are equal.
	for (size_t i = 0; i < this->_nElements; ++i)
	{
		//if (this->m_MData[i] != rhs.m_MData[i])
		if (!CloseEnough(this->_MData[i], rhs._MData[i]))
			return false;
	}
	return true;
}

/* **************************************************************************************************
THE ASSIGNMENT (=) OPERATOR
/* *************************************************************************************************/
template <class T>
Matrix<T> Matrix<T>::operator= (const Matrix<T>& rhs)
{
	// Make sure we're not assigning to ourself.
	if (this != &rhs)
	{
		_nRows = rhs._nRows;
		_nCols = rhs._nCols;
		_nElements = rhs._nElements;

		if (_MData)
			delete[] _MData;

		_MData = new T[_nElements];
		for (size_t i = 0; i < _nElements; i++)
			_MData[i] = rhs._MData[i];
	}

	return *this;

}

template<class T>
Matrix<T> Matrix<T>::operator*=(const T& rhs)
{
	size_t count = _nElements;
	for (size_t i = 0; i < _nElements;i++)
		_MData[i] *= rhs;
	return *this;
}

template<class T>
inline Matrix<T> Matrix<T>::operator*=(const Matrix<T>& rhs)
{
	return (*this) * rhs;
}

/* **************************************************************************************************
SEPARATE THE MATRIX INTO TWO PARTS, AROUND THE COLUMN NUMBER PROVIDED
(Note that the output is returned into the two Matrix<T> pointers in the input argument list)
/* *************************************************************************************************/
template <class T>
bool Matrix<T>::Separate(Matrix<T>& matrix1, Matrix<T>& matrix2, size_t colNum)
{
	// Compute the sizes of the new matrices.
	size_t numRows = _nRows;
	size_t numCols1 = colNum;
	size_t numCols2 = _nCols - colNum;

	// Resize the two matrices to the proper dimensions.
	matrix1.Resize(numRows, numCols1);
	matrix2.Resize(numRows, numCols1);

	// Loop over the original matrix and store data into the appropriate elements of the two
	// output matrices.
	for (size_t row = 0; row < _nRows; ++row)
	{
		for (size_t col = 0; col < _nCols; ++col)
		{
			if (col < colNum)
				matrix1.Set(row, col, this->Get(row, col));
			else
				matrix2.Set(row, col - colNum, this->Get(row, col));
		}
	}
	return true;
}

/* **************************************************************************************************
JOIN TwO MATRICES TOGETHER
/* *************************************************************************************************/
template <class T>
bool Matrix<T>::Join(const Matrix<T>& matrix2)
{
	// Extract the information that we need from both matrices
	size_t numRows1 = _nRows;
	size_t numRows2 = matrix2._nRows;
	size_t numCols1 = _nCols;
	size_t numCols2 = matrix2._nCols;

	// If the matrices have different numbers of rows, then this operation makes no sense.
	if (numRows1 != numRows2)
		throw std::invalid_argument("Attempt to join matrices with different numbers of rows is invalid.");

	// Allocate memory for the result.
	// Note that only the number of columns increases.
	T* newMData = new T[numRows1 * (numCols1 + numCols2)];

	// Copy the two matrices into the new one.
	size_t linearIndex, resultLinearIndex;
	for (size_t i = 0; i < numRows1; ++i)
	{
		for (size_t j = 0; j < numCols1 + numCols2; ++j)
		{
			resultLinearIndex = (i * (numCols1 + numCols2)) + j;

			// If j is in the left hand matrix, we get data from there...
			if (j < numCols1)
			{
				linearIndex = (i * numCols1) + j;
				newMData[resultLinearIndex] = _MData[linearIndex];
			}
			// Otherwise, j must be in the right hand matrix, so we get data from there...
			else
			{
				linearIndex = (i * numCols2) + (j - numCols1);
				newMData[resultLinearIndex] = matrix2._MData[linearIndex];
			}
		}
	}

	// Update the stored data.
	_nCols = numCols1 + numCols2;
	_nElements = _nRows * _nCols;
	delete[] _MData;
	_MData = new T[_nElements];
	for (size_t i = 0; i < _nElements; ++i)
		_MData[i] = newMData[i];

	delete[] newMData;
	return true;
}

/* **************************************************************************************************
COMPUTE MATRIX DETERMINANT
/* *************************************************************************************************/
template <class T>
T Matrix<T>::Determinant()
{
	// Check if the matrix is square.
	if (!IsSquare())
		throw std::invalid_argument("Cannot compute the determinant of a matrix that is not square.");

	// If the matrix is 2x2, we can just compute the determinant directly.
	T determinant;
	if (_nRows == 2)
	{
		determinant = (_MData[0] * _MData[3]) - (_MData[1] * _MData[2]);
	}
	else
	{
		/* Otherwise we extract the sub-matrices and then recursively call this function
			until we get to 2x2 matrices. */

			// We will find the sub-matrices for row 0.
			// So, loop over each column.
		T cumulativeSum = 0.0;
		T sign = 1.0;
		for (size_t j = 0; j < _nCols; ++j)
		{
			// And find the sub-matrix for each element.
			Matrix<T> subMatrix = this->FindSubMatrix(0, j);

			/* Cumulatively multiply the determinant of the sub-matrix by the
				current element of this matrix and the sign variable (note the
				recursive calling of the Determinant() method). */
			cumulativeSum += this->Get(0, j) * subMatrix.Determinant() * sign;
			sign = -sign;
		}
		determinant = cumulativeSum;
	}

	return determinant;
}


/* **************************************************************************************************
COMPUTE MATRIX INVERSE (USING GAUSS-JORDAN ELIMINATION)
/* *************************************************************************************************/
template <class T>
bool Matrix<T>::Inverse()
{
	// Check if the matrix is square (we cannot compute the inverse if it isn't).
	if (!IsSquare())
		throw std::invalid_argument("Cannot compute the inverse of a matrix that is not square.");

	// If we get to here, the matrix is square so we can continue.

	// Form an identity matrix with the same dimensions as the matrix we wish to invert.
	Matrix<T> identityMatrix(_nRows, _nCols);
	identityMatrix.SetToIdentity();

	// Join the identity matrix to the existing matrix.	
	size_t originalNumCols = _nCols;
	Join(identityMatrix);

	// Begin the main part of the process.
	size_t cRow, cCol;
	int maxCount = 100;
	int count = 0;
	bool completeFlag = false;
	while ((!completeFlag) && (count < maxCount))
	{
		for (size_t diagIndex = 0; diagIndex < _nRows; ++diagIndex)
		{
			// Loop over the diagonal of the matrix and ensure all diagonal elements are equal to one.
			cRow = diagIndex;
			cCol = diagIndex;

			// Find the index of the maximum element in the current column.
			size_t maxIndex = FindRowWithMaxElement(cCol, cRow);

			// If this isn't the current row, then swap.
			if (maxIndex != cRow)
			{
				//std::cout << "Swap rows " << cRow << " and " << maxIndex << std::endl;
				SwapRow(cRow, maxIndex);
			}
			// Make sure the value at (cRow,cCol) is equal to one.
			if (_MData[Sub2Ind(cRow, cCol)] != 1.0)
			{
				T multFactor = 1.0 / _MData[Sub2Ind(cRow, cCol)];
				MultRow(cRow, multFactor);
				//std::cout << "Multiply row " << cRow << " by " << multFactor << std::endl;
			}

			// Consider the column.
			for (size_t rowIndex = cRow + 1; rowIndex < _nRows; ++rowIndex)
			{
				// If the element is already zero, move on.
				if (!CloseEnough(_MData[Sub2Ind(rowIndex, cCol)], 0.0))
				{
					// Obtain the element to work with from the matrix diagonal.
					// As we aim to set all the diagonal elements to one, this should
					// always be valid for a matrix that can be inverted.
					size_t rowOneIndex = cCol;

					// Get the value stored at the current element.
					T currentElementValue = _MData[Sub2Ind(rowIndex, cCol)];

					// Get the value stored at (rowOneIndex, cCol)
					T rowOneValue = _MData[Sub2Ind(rowOneIndex, cCol)];

					// If this is equal to zero, then just move on.
					if (!CloseEnough(rowOneValue, 0.0))
					{
						// Compute the correction factor.
						// (required to reduce the element at (rowIndex, cCol) to zero).
						T correctionFactor = -(currentElementValue / rowOneValue);

						MultAdd(rowIndex, rowOneIndex, correctionFactor);

						//std::cout << "Multiply row " << rowOneIndex << " by " << correctionFactor <<
						//	" and add to row " << rowIndex << std::endl;
					}
				}
			}

			// Consider the row.			
			for (size_t colIndex = cCol + 1; colIndex < originalNumCols; ++colIndex)
			{
				// If the element is already zero, move on.
				if (!CloseEnough(_MData[Sub2Ind(cRow, colIndex)], 0.0))
				{
					// Obtain the element to work with from the matrix diagonal.
					// As we aim to set all the diagonal elements to one, this should
					// always be valid for a matrix that can be inverted.
					size_t rowOneIndex = colIndex;

					// Get the value stored at the current element.
					T currentElementValue = _MData[Sub2Ind(cRow, colIndex)];

					// Get the value stored at (rowOneIndex, colIndex)
					T rowOneValue = _MData[Sub2Ind(rowOneIndex, colIndex)];

					// If this is equal to zero, then just move on.
					if (!CloseEnough(rowOneValue, 0.0))
					{

						// Compute the correction factor.
						// (required to reduce the element at (cRow, colIndex) to zero).
						T correctionFactor = -(currentElementValue / rowOneValue);

						// To make this equal to zero, we need to add -currentElementValue multiplied by
						// the row at rowOneIndex.
						MultAdd(cRow, rowOneIndex, correctionFactor);

						//std::cout << "Multiply row " << rowOneIndex << " by " << correctionFactor <<
						//	" and add to row " << cRow << std::endl;
					}
				}
			}
		}

		// Separate the result into the left and right halves.
		Matrix<T> leftHalf;
		Matrix<T> rightHalf;
		this->Separate(leftHalf, rightHalf, originalNumCols);

		// When the process is complete, the left half should be the identity matrix.
		if (leftHalf == identityMatrix)
		{
			// Set completedFlag to true to indicate that the process has completed.
			completeFlag = true;

			// Rebuild the matrix with just the right half, which now contains the result.			
			_nCols = originalNumCols;
			_nElements = _nRows * _nCols;
			delete[] _MData;
			_MData = new T[_nElements];
			for (size_t i = 0; i < _nElements; ++i)
				_MData[i] = rightHalf._MData[i];
		}

		// Increment the counter.
		count++;
	}

	// Return whether the process succeeded or not.
	return completeFlag;
}

/* **************************************************************************************************
COMPUTE AND RETURN THE TRANSPOSE
/* *************************************************************************************************/
template <class T>
Matrix<T> Matrix<T>::Transpose() const
{
	// Form the output matrix.
	// Note that we reverse the order of rows and columns, as this will be the transpose.
	Matrix<T> resultMatrix(_nCols, _nRows);

	// Now loop through the elements and copy in the appropriate order.
	for (size_t i = 0; i < _nRows; ++i)
		for (size_t j = 0; j < _nCols; ++j)
			resultMatrix.Set(j, i, this->Get(i, j));

	return resultMatrix;
}

/* **************************************************************************************************
CONVERT TO ROW ECHELON FORM (USING GAUSSIAN ELIMINATION)
/* *************************************************************************************************/
template <class T>
Matrix<T> Matrix<T>::RowEchelon()
{
	/* The current matrix must have at least as many columns as rows, but note that we don't
		actually require it to be square since we assume that the user may have combined a
		square matrix with a vector. They would do this, for example, if they were trying to
		solve a system of linear equations. */
	if (_nCols < _nRows)
		throw std::invalid_argument("The matrix must have at least as many columns as rows.");

	/* Make a copy of the matrix data before we start. We do this because the procedure below
		will make changes to the stored matrix data (it operates 'in place') and we don't want
		this behaviour. Therefore we take a copy at the beginning and then we will replace the
		modified matrix data with this copied data at the end, thus preserving the original. */
	T* tempMData;
	tempMData = new T[_nRows * _nCols];
	for (size_t i = 0; i < (_nRows * _nCols); ++i)
		tempMData[i] = _MData[i];

	// Begin the main part of the process.
	size_t cRow, cCol;
	int maxCount = 100;
	int count = 0;
	bool completeFlag = false;
	while (!completeFlag && count < maxCount)
	{
		for (size_t diagIndex = 0; diagIndex < _nRows; ++diagIndex)
		{
			// Loop over the diagonal of the matrix and ensure all diagonal elements are equal to one.
			cRow = diagIndex;
			cCol = diagIndex;

			// Find the index of the maximum element in the current column.
			size_t maxIndex = FindRowWithMaxElement(cCol, cRow);

			// Now consider the column.
			// Our aim is to set all elements BELOW the diagonal to zero.
			for (size_t rowIndex = cRow + 1; rowIndex < _nRows; ++rowIndex)
			{
				// If the element is already zero, move on.
				if (!CloseEnough(_MData[Sub2Ind(rowIndex, cCol)], 0.0))
				{
					size_t rowOneIndex = cCol;

					// Get the value stored at the current element.
					T currentElementValue = _MData[Sub2Ind(rowIndex, cCol)];

					// Get the value stored at (rowOneIndex, cCol)
					T rowOneValue = _MData[Sub2Ind(rowOneIndex, cCol)];

					// If this is equal to zero, then just move on.
					if (!CloseEnough(rowOneValue, 0.0))
					{
						// Compute the correction factor.
						// (required to reduce the element at (rowIndex, cCol) to zero).
						T correctionFactor = -(currentElementValue / rowOneValue);
						MultAdd(rowIndex, rowOneIndex, correctionFactor);
					}
				}
			}
		}

		/* Test whether we have achieved the desired result of converting the
			matrix into row-echelon form. */
		completeFlag = this->IsRowEchelon();

		// Increment the counter.
		count++;
	}

	// Form the output matrix.
	Matrix<T> outputMatrix(_nRows, _nCols, _MData);

	// Restore the original matrix data from the copy.
	for (size_t i = 0; i < (_nRows * _nCols); ++i)
		_MData[i] = tempMData[i];

	// Delete the copy.
	delete[] tempMData;

	return outputMatrix;
}

/* **************************************************************************************************
COMPUTE THE RANK OF THE PROVIDED MATRIX
/* *************************************************************************************************/
template <class T>
size_t Matrix<T>::Rank()
{
	// Convert the matrix to row-echelon form.
	Matrix<T> matrixCopy = this->RowEchelon();

	/* If this didn't work, then we compute the rank by finding
		the largest non-zero sub-matrix with a non-zero determinant.

		Note that this method is slower for large matrices and therefore
		it is better to use the RowEchelon method if possible. */
	size_t numNonZeroRows = 0;
	if (!matrixCopy.IsRowEchelon())
	{
		// Setup a std::vector to store the sub-matrices as we go.
		std::vector<Matrix<T>> subMatrixVector;

		// Store the current matrix into the array first.
		subMatrixVector.push_back(*this);

		/* Loop through the subMatrixVector until either we have tested every
			sub-matrix or the completeFlag is set. */
		bool completeFlag = false;
		int subMatrixCount = 0;
		while ((subMatrixCount < subMatrixVector.size()) && (!completeFlag))
		{
			// Extract the currentMatrix to work with.
			Matrix<T> currentMatrix = subMatrixVector[subMatrixCount];
			subMatrixCount++;

			// Test if this matrix is non-zero.
			if (currentMatrix.IsNonZero())
			{
				// If the determinant is non-zero, then we have our result.
				T currentMDet = currentMatrix.Determinant();
				if (!CloseEnough(currentMDet, 0.0))
				{
					completeFlag = true;
					numNonZeroRows = currentMatrix.RowsCount();
				}
				else
				{
					// Extract and store each sub-matrix (if larger than 2x2).
					if ((currentMatrix.RowsCount() > 2) && (currentMatrix.ColsCount() > 2))
					{
						for (int i = 0; i < currentMatrix.RowsCount(); ++i)
						{
							for (int j = 0; j < currentMatrix.ColsCount(); ++j)
							{
								// Extract this sub-matrix and store.
								subMatrixVector.push_back(currentMatrix.FindSubMatrix(i, j));
							}
						}
					}
				}
			}
		}
	}
	else
	{
		/* Converting to row echelon form did work, so we can simply
			count the number of non-zero rows to get the rank. */

			/* If we get to here, then we can assume that the matrix is now
				in row-echelon form and we can compute the rank quite easily
				as simply the number of non-zero rows. */

		size_t nRows = matrixCopy.RowsCount();
		size_t nCols = matrixCopy.ColsCount();

		// Loop over each row and test whether it has at least one non-zero element.
		for (size_t i = 0; i < nRows; ++i)
		{
			// Loop over the columns of this row.
			size_t colSum = 0;
			for (size_t j = 0; j < nCols; ++j)
			{
				if (!CloseEnough(matrixCopy.Get(i, j), 0.0))
					colSum++;
			}
			// If colSum is greater than zero, then increment numNonZeroRows.
			if (colSum > 0)
				numNonZeroRows++;
		}

	}
	// The rank of the matrix is simply the number of non-zero rows.
	return numNonZeroRows;

}

/* **************************************************************************************************
PRIVATE FUNCTIONS
/* *************************************************************************************************/
// Function to return the linear index corresponding to the supplied row and column values.
template <class T>
size_t Matrix<T>::Sub2Ind(size_t row, size_t col) const
{
	if (row < _nRows && col < _nCols)
		return row * _nCols + col;

	throw std::invalid_argument("row and col are too large");
	//return -1;
}

// Function to test whether the matrix is square.
template <class T>
bool Matrix<T>::IsSquare()
{
	return _nCols == _nRows;
}

// Function to test whether the matrix is non-zero.
template <class T>
bool Matrix<T>::IsNonZero()
{
	// Loop over every element.
	int numNonZero = 0;
	for (size_t i = 0; i < _nElements; ++i)
	{
		// If this element is close enough to zero, then
		// increment our numNonZero counter.
		if (!CloseEnough(_MData[i], 0.0))
			numNonZero++;
	}

	/* If the numNonZero counter is still equal to zero, then
		the matrix must be all zeros, hence we return false.
		Otherwise we return true. */
	return numNonZero != 0;
}

// Function to test whether the matrix is in row-echelon form.
template <class T>
bool Matrix<T>::IsRowEchelon()
{
	/* We do this by testing that the sum of all the elements in the
		lower triangular matrix is zero. */
		// Loop over each row, except the first one (which doesn't need to have any zero elements).
	T cumulativeSum = static_cast<T>(0.0);
	for (size_t i = 1; i < _nRows; ++i)
	{
		/* Loop over the columns that correspond to the lower triangular
			matrix according to the current row. */
		for (size_t j = 0; j < i; ++j)
		{
			// Add this element to the cumulative sum.
			cumulativeSum += _MData[Sub2Ind(i, j)];
		}
	}

	/* If the matrix is in row-echelon form, then cumulative sum should
		still equal zero, otherwise the matrix cannot be in row-echelon form. */
	return CloseEnough(cumulativeSum, 0.0);
}

// Function to test whether the matrix is symmetric.
template <class T>
bool Matrix<T>::IsSymmetric()
{
	/* First test that the matrix is square, if it is
		not, then it cannot by symmetric. */
	if (!this->IsSquare())
		return false;

	// Now test for symmetry about the diagonal.
	T currentRowElement = static_cast<T>(0.0);
	T currentColElement = static_cast<T>(0.0);
	bool returnFlag = true;
	int diagIndex = 0;
	while ((diagIndex < _nCols) && returnFlag)
	{
		int rowIndex = diagIndex + 1;
		while ((rowIndex < _nRows) && returnFlag)
		{
			currentRowElement = this->Get(rowIndex, diagIndex);
			currentColElement = this->Get(diagIndex, rowIndex);

			// Compare the row and column elements.
			if (!CloseEnough(currentRowElement, currentColElement))
				returnFlag = false;

			// Increment row index.
			rowIndex++;
		}

		// Increment diagIndex.
		diagIndex++;

	}

	// Return the result.
	return returnFlag;

}

// Function to swap rows i and j (in place).
template <class T>
void Matrix<T>::SwapRow(size_t i, size_t j)
{
	// Store a tempory copy of row i.
	T* tempRow = new T[_nCols];
	for (size_t k = 0; k < _nCols; ++k)
		tempRow[k] = _MData[Sub2Ind(i, k)];

	// Replace row i with row j.
	for (size_t k = 0; k < _nCols; ++k)
		_MData[Sub2Ind(i, k)] = _MData[Sub2Ind(j, k)];

	// Replace row k with the tempory copy of the original row i.
	for (size_t k = 0; k < _nCols; ++k)
		_MData[Sub2Ind(j, k)] = tempRow[k];

	// Tidy up after ourselves.
	delete[] tempRow;
}

// Function to add a multiple of row j to row i (in place).
template <class T>
void Matrix<T>::MultAdd(size_t i, size_t j, T multFactor)
{
	for (size_t k = 0; k < _nCols; ++k)
		_MData[Sub2Ind(i, k)] += (_MData[Sub2Ind(j, k)] * multFactor);
}

// Function to the find the row with the maximum element at the column given.
// Returns the row index.
template <class T>
size_t Matrix<T>::FindRowWithMaxElement(size_t colNumber, size_t startingRow)
{
	T tempValue = _MData[Sub2Ind(startingRow, colNumber)];
	size_t rowIndex = startingRow;
	for (size_t k = startingRow + 1; k < _nRows; ++k)
	{
		if (fabs(_MData[Sub2Ind(k, colNumber)]) > fabs(tempValue))
		{
			rowIndex = k;
			tempValue = _MData[Sub2Ind(k, colNumber)];
		}
	}
	return rowIndex;
}

// Function to multiply a row by the given value.
template <class T>
void Matrix<T>::MultRow(size_t i, T multFactor)
{
	for (size_t k = 0; k < _nCols; ++k)
		_MData[Sub2Ind(i, k)] *= multFactor;
}

// A simple function to print a matrix to stdout.
template <class T>
void Matrix<T>::Print() const
{
	for (size_t row = 0; row < _nRows; ++row)
	{
		for (size_t col = 0; col < _nCols; ++col)
			std::cout << std::fixed << std::setprecision(6) << this->Get(row, col) << "  ";

		std::cout << std::endl;
	}
}

// A simple function to print a matrix to stdout, with specified precision.
template <class T>
void Matrix<T>::Print(int precision) const
{
	for (size_t row = 0; row < _nRows; ++row)
	{
		for (size_t col = 0; col < _nCols; ++col)
			std::cout << std::fixed << std::setprecision(precision) << this->Get(row, col) << "  ";

		std::cout << std::endl;
	}
}

template <class T>
bool Matrix<T>::CloseEnough(T f1, T f2)
{
	return fabs(f1 - f2) < 1e-9;
}

// Function to find the sub-matrix for the given element.
template <class T>
Matrix<T> Matrix<T>::FindSubMatrix(size_t rowNum, size_t colNum)
{
	// Create a new matrix to store the sub-matrix.
	// Note that this is one row and one column smaller than the original.
	Matrix<T> subMatrix(_nRows - 1, _nCols - 1);

	// Loop over the elements of the existing matrix and copy to sub-matrix as appropriate.
	int count = 0;
	for (size_t i = 0; i < _nRows; ++i)
	{
		for (size_t j = 0; j < _nCols; ++j)
		{
			// If i or j correspond to rowNum or colNum, then ignore this element.
			if ((i != rowNum) && (j != colNum))
			{
				subMatrix._MData[count] = this->Get(i, j);
				count++;
			}
		}
	}

	return subMatrix;
}


#endif
