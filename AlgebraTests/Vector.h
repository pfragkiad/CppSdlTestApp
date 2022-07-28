#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

template <class T>
class Vector
{
public:
	// Define the various constructors.
	// Default.
	Vector();

	// With a single integer specifying the number of dimensions.
	Vector(int numDims);

	// With input data (std::vector).
	Vector(std::vector<T> inputData);

	// And the destructor.
	~Vector();

	// Functions to return parameters of the vector.
	size_t GetNumDims() const;

	// Functions to handle elements of the vector.
	T GetElement(int index) const;
	void SetElement(int index, T value);

	// Functions to perform computations on the vector.
	// Return the length of the vector.
	T norm();

	// Return a normalized copy of the vector.
	Vector<T> Normalized();

	// Normalize the vector in place.
	void Normalize();

	// Overloaded operators.
	Vector<T> operator+ (const Vector<T>& rhs) const;
	Vector<T> operator- (const Vector<T>& rhs) const;
	Vector<T> operator* (const T& rhs) const;
	//mine
	void operator*= (const T& rhs);
	void operator/= (const T& rhs);

	// Friend functions.
	template <class T> friend Vector<T> operator* (const T& lhs, const Vector<T>& rhs);

	//normalize e.g. !v1
	template <class T> friend Vector<T> operator! (const Vector<T>& rhs);

	// Static functions.
	static T dot(const Vector<T>& a, const Vector<T>& b);
	static Vector<T> cross(const Vector<T>& a, const Vector<T>& b);

	void inline Print()
	{
		for (int row = 0; row < _nDims; ++row)
			std::cout << std::fixed << std::setprecision(6) << _vectorData.at(row) << std::endl;
	}

private:
	std::vector<T> _vectorData;
	size_t _nDims;

};

// A simple function to print a vector to stdout.
template <class T>
void PrintVector(Vector<T> inputVector)
{
	size_t nRows = inputVector.GetNumDims();
	for (int row = 0; row < nRows; ++row)
		std::cout << std::fixed << std::setprecision(6) << inputVector.GetElement(row) << std::endl;
}

/* **************************************************************************************************
CONSTRUCTOR / DESTRUCTOR FUNCTIONS
/* *************************************************************************************************/
// The default constructor.
template <class T>
Vector<T>::Vector()
{
	_nDims = 0;
	_vectorData = std::vector<T>();
}

template <class T>
Vector<T>::Vector(int numDims)
{
	_nDims = numDims;
	_vectorData = std::vector<T>(numDims, static_cast<T>(0.0));
}

template <class T>
Vector<T>::Vector(std::vector<T> inputData)
{
	_nDims = inputData.size();
	_vectorData = inputData;
}

template <class T>
Vector<T>::~Vector()
{
	// For now, we don't need to do anything in the destructor.
}

/* **************************************************************************************************
FUNCTIONS TO RETURN PARAMETERS
/* *************************************************************************************************/
template <class T>
size_t Vector<T>::GetNumDims() const
{
	return _nDims;
}

/* **************************************************************************************************
FUNCTIONS TO HANDLE ELEMENTS OF THE VECTOR
/* *************************************************************************************************/
template <class T>
T Vector<T>::GetElement(int index) const
{
	return _vectorData[index];
}

template <class T>
void Vector<T>::SetElement(int index, T value)
{
	_vectorData[index] = value;
}

/* **************************************************************************************************
FUNCTIONS TO PERFORM COMPUTATIONS ON THE VECTOR
/* *************************************************************************************************/
// Compute the length of the vector,known as the 'norm'.
template <class T>
T Vector<T>::norm()
{
	T cumulativeSum = static_cast<T>(0.0);
	for (int i = 0; i < _nDims; ++i)
		cumulativeSum += _vectorData.at(i) * _vectorData.at(i);

	return sqrt(cumulativeSum);
}

// Return a normalized copy of the vector.
template <class T>
Vector<T> Vector<T>::Normalized()
{
	// Compute the vector norm.
	T vecNorm = this->norm();

	// Compute the normalized version of the vector.
	Vector<T> result(_vectorData);
	return result * (static_cast<T>(1.0) / vecNorm);
}

// Normalize the vector in place.
template <class T>
void Vector<T>::Normalize()
{
	// Compute the vector norm.
	T vecNorm = this->norm();

	// Compute the elements of the normalized version of the vector.
	for (int i = 0; i < _nDims; ++i)
	{
		T temp = _vectorData.at(i) * (static_cast<T>(1.0) / vecNorm);
		_vectorData.at(i) = temp;
	}
}

/* **************************************************************************************************
OVERLOADED OPERATORS
/* *************************************************************************************************/
template <class T>
Vector<T> Vector<T>::operator+ (const Vector<T>& rhs) const
{
	// Check that the number of dimensions match.
	if (_nDims != rhs._nDims)
		throw std::invalid_argument("Vector dimensions do not match.");

	//std::vector<T> resultData;
	//for (int i = 0; i < m_nDims; ++i)
	//	resultData.push_back(m_vectorData.at(i) + rhs.m_vectorData.at(i));
	std::vector<T> resultData(_vectorData);
	for (int i = 0; i < _nDims; ++i)
		resultData.at(i) += rhs._vectorData.at(i);

	Vector<T> result(resultData);
	return result;
}

template <class T>
Vector<T> Vector<T>::operator- (const Vector<T>& rhs) const
{
	// Check that the number of dimensions match.
	if (_nDims != rhs._nDims)
		throw std::invalid_argument("Vector dimensions do not match.");

	std::vector<T> resultData;
	for (int i = 0; i < _nDims; ++i)
		resultData.push_back(_vectorData.at(i) - rhs._vectorData.at(i));

	Vector<T> result(resultData);
	return result;
}

template <class T>
Vector<T> Vector<T>::operator* (const T& rhs) const
{
	// Perform scalar multiplication.
	std::vector<T> resultData;
	for (int i = 0; i < _nDims; ++i)
		resultData.push_back(_vectorData.at(i) * rhs);

	Vector<T> result(resultData);
	return result;
}

//mine
template <class T>
void Vector<T>::operator*= (const T& rhs) ///////////
{
	// Perform scalar multiplication.
	for (int i = 0; i < _nDims; ++i)
		_vectorData.at(i) *= rhs;
}

template <class T>
void Vector<T>::operator/= (const T& rhs) ///////////
{
	// Perform scalar multiplication.
	for (int i = 0; i < _nDims; ++i)
		_vectorData.at(i) /= rhs;
}


//--

/* **************************************************************************************************
FRIEND FUNCTIONS
/* *************************************************************************************************/
template <class T>
Vector<T> operator* (const T& lhs, const Vector<T>& rhs)
{
	// Perform scalar multiplication.
	//std::vector<T> resultData;
	//for (int i=0; i<rhs.m_nDims; ++i)
	//	resultData.push_back(lhs * rhs.m_vectorData.at(i))
	std::vector<T> resultData(rhs._vectorData);
	for (int i = 0; i < rhs._nDims; ++i)
		resultData.at(i) *= lhs;

	Vector<T> result(resultData);
	return result;
}

template<class T>
inline Vector<T> operator!(const Vector<T>& rhs)
{
	return rhs.Normalized();
}

/* **************************************************************************************************
STATIC FUNCTIONS
/* *************************************************************************************************/
template <class T>
T Vector<T>::dot(const Vector<T>& a, const Vector<T>& b)
{
	// Check that the number of dimensions match.
	if (a._nDims != b._nDims)
		throw std::invalid_argument("Vector dimensions must match for the dot-product to be computed.");

	// Compute the dot product.
	T cumulativeSum = static_cast<T>(0.0);
	for (int i = 0; i < a._nDims; ++i)
		cumulativeSum += a._vectorData.at(i) * b._vectorData.at(i);

	return cumulativeSum;
}

template <class T>
Vector<T> Vector<T>::cross(const Vector<T>& a, const Vector<T>& b)
{
	// Check that the number of dimensions match.
	if (a._nDims != b._nDims)
		throw std::invalid_argument("Vector dimensions must match for the cross-product to be computed.");

	// Check that the number of dimensions is 3.
	/* Although the cross-product is also defined for 7 dimensions, we are
		not going to consider that case at this time. */
	if (a._nDims != 3)
		throw std::invalid_argument("The cross-product can only be computed for three-dimensional vectors.");

	// Compute the cross product.
	std::vector<T> resultData;
	resultData.push_back((a._vectorData.at(1) * b._vectorData.at(2)) - (a._vectorData.at(2) * b._vectorData.at(1)));
	resultData.push_back(-((a._vectorData.at(0) * b._vectorData.at(2)) - (a._vectorData.at(2) * b._vectorData.at(0))));
	resultData.push_back((a._vectorData.at(0) * b._vectorData.at(1)) - (a._vectorData.at(1) * b._vectorData.at(0)));

	Vector<T> result(resultData);
	return result;
}

#endif