#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

template <class T>
class Vector
{
public:
	// Define the various constructors.
	// Default.
	Vector();

	// With a single integer specifying the number of dimensions.
	Vector(size_t numDims);

	// With input data (std::vector).
	Vector(std::vector<T> inputData);

	Vector(std::initializer_list<T> data);

	// And the destructor.
	~Vector();

	// Functions to return parameters of the vector.
	size_t DimsCount() const;

	// Functions to handle elements of the vector.
	T Get(size_t index) const;
	void Set(size_t index, T value);

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
	T operator* (const Vector<T>& rhs) const; //dot product

	Vector<T> operator/ (const T& rhs) const;
	void operator*= (const T& rhs);
	void operator/= (const T& rhs);

	T operator [](int i) const;
	T& operator[](int i);

	// Friend functions.
	template <class T> friend Vector<T> operator* (const T& lhs, const Vector<T>& rhs);
	//normalize e.g. !v1
	template <class T> friend Vector<T> operator! (const Vector<T>& rhs);
	template <class T> friend Vector<T> operator^ (const Vector<T>& lhs, const Vector<T>& rhs);
	template <class T> friend Vector<T> operator- ( const Vector<T>& rhs);
	template <class T> friend Vector<T> operator/ (const T& lhs, const Vector<T>& rhs);


	// Static functions.
	static T dot(const Vector<T>& a, const Vector<T>& b);
	static Vector<T> cross(const Vector<T>& a, const Vector<T>& b);

	template <class T> friend std::ostream& operator << (std::ostream& os, const Vector<T>& v);

	void inline Print() const
	{
		for (int row = 0; row < _nDims; ++row)
			std::cout << _VData.at(row) << std::endl;
	}

	void inline Print(int precision) const
	{
		for (int row = 0; row < _nDims; ++row)
			std::cout << std::fixed << std::setprecision(precision) << _VData.at(row) << std::endl;
	}


private:
	std::vector<T> _VData;
	size_t _nDims;
};


//// A simple function to print a vector to stdout.
//template <class T>
//void PrintVector(Vector<T> inputVector)
//{
//	size_t nRows = inputVector.GetNumDims();
//	for (int row = 0; row < nRows; ++row)
//		std::cout << std::fixed << std::setprecision(6) << inputVector.GetElement(row) << std::endl;
//}

template<class T>
std::ostream& operator << (std::ostream& os, const Vector<T>& v)
{
	for (size_t row = 0; row < v._nDims; ++row)
		//os << std::fixed << std::setprecision(6) << v.GetElement(row) << std::endl;
		os << std::fixed << std::setprecision(6) << v._VData[row] << std::endl;
	return os;
}

/* **************************************************************************************************
CONSTRUCTOR / DESTRUCTOR FUNCTIONS
/* *************************************************************************************************/
// The default constructor.
template <class T>
Vector<T>::Vector()
{
	_nDims = 0;
	_VData = std::vector<T>();
}

template <class T>
Vector<T>::Vector(size_t numDims)
{
	_nDims = numDims;
	_VData = std::vector<T>(numDims, static_cast<T>(0.0));
}

template <class T>
Vector<T>::Vector(std::vector<T> inputData)
{
	_nDims = inputData.size();
	_VData = inputData;
}

template <class T>
Vector<T>::Vector(std::initializer_list<T> data)
{
	_nDims = data.size();
	_VData = std::vector<T>(data);
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
size_t Vector<T>::DimsCount() const
{
	return _nDims;
}

/* **************************************************************************************************
FUNCTIONS TO HANDLE ELEMENTS OF THE VECTOR
/* *************************************************************************************************/
template <class T>
T Vector<T>::Get(size_t index) const
{
	return _VData[index];
}

template <class T>
void Vector<T>::Set(size_t index, T value)
{
	_VData[index] = value;
}

/* **************************************************************************************************
FUNCTIONS TO PERFORM COMPUTATIONS ON THE VECTOR
/* *************************************************************************************************/
// Compute the length of the vector, known as the 'norm'.
template <class T>
T Vector<T>::norm()
{
	T cumulativeSum = static_cast<T>(0.0);
	for (int i = 0; i < _nDims; ++i)
		cumulativeSum += _VData.at(i) * _VData.at(i);

	return sqrt(cumulativeSum);
}

// Return a normalized copy of the vector.
template <class T>
Vector<T> Vector<T>::Normalized()
{
	// Compute the vector norm.
	//T length = norm();

	//// Compute the normalized version of the vector.
	//Vector<T> result(_VData);
	//return result * (static_cast<T>(1.0) / vecNorm);
	return Vector<T>(_VData) / norm();
}

// Normalize the vector in place.
template <class T>
void Vector<T>::Normalize()
{
	// Compute the vector norm.
	T length = norm();

	// Compute the elements of the normalized version of the vector.
	for (int i = 0; i < _nDims; ++i)
	{
		//T temp = _VData.at(i) / vecNorm; //;* (static_cast<T>(1.0) / vecNorm);
		//_VData.at(i) = temp;
		_VData.at(i) /= length;
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
	//	resultData.push_back(m_VData.at(i) + rhs.m_VData.at(i));
	std::vector<T> resultData(_VData);
	for (int i = 0; i < _nDims; ++i)
		resultData.at(i) += rhs._VData.at(i);

	Vector<T> result(resultData);
	return result;
}

template <class T>
Vector<T> Vector<T>::operator- (const Vector<T>& rhs) const
{
	// Check that the number of dimensions match.
	if (_nDims != rhs._nDims)
		throw std::invalid_argument("Vector dimensions do not match.");

	//std::vector<T> resultData;
	//for (int i = 0; i < _nDims; ++i)
	//	resultData.push_back(_VData.at(i) - rhs._VData.at(i));
	std::vector<T> resultData(_VData);
	for (int i = 0; i < _nDims; ++i)
		resultData.at(i) -= rhs._VData.at(i);

	Vector<T> result(resultData);
	return result;
}

template <class T>
Vector<T> Vector<T>::operator* (const T& rhs) const
{
	// Perform scalar multiplication.
	//std::vector<T> resultData;
	//for (int i = 0; i < _nDims; ++i)
	//	resultData.push_back(_VData.at(i) * rhs);
	std::vector<T> resultData(_VData);
	for (int i = 0; i < _nDims; ++i)
		resultData.at(i) *= rhs;

	return Vector<T>(resultData);
}

template <class T>
T Vector<T>::operator*(const Vector<T>& rhs) const //dot product
{
	return dot(*this, rhs);
}

template <class T>
Vector<T> Vector<T>::operator/ (const T& rhs) const
{
	std::vector<T> resultData(_VData);
	for (int i = 0; i < _nDims; ++i)
		resultData.at(i) /= rhs;

	//Vector<T> result(resultData);
	//return result;
	return Vector<T>(resultData);
}

//mine
template <class T>
void Vector<T>::operator*= (const T& rhs) ///////////
{
	// Perform scalar multiplication.
	for (int i = 0; i < _nDims; ++i)
		_VData.at(i) *= rhs;
}

template <class T>
void Vector<T>::operator/= (const T& rhs) ///////////
{
	// Perform scalar multiplication.
	for (int i = 0; i < _nDims; ++i)
		_VData.at(i) /= rhs;
}


//https://stackoverflow.com/questions/11066564/overload-bracket-operators-to-get-and-set
template <class T>
T Vector<T>::operator [](int i) const { return _VData[i]; }

template<class T>
T& Vector<T>::operator[](int i) { return _VData[i]; }


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
	//	resultData.push_back(lhs * rhs.m_VData.at(i))
	std::vector<T> resultData(rhs._VData);
	for (int i = 0; i < rhs._nDims; ++i)
		resultData.at(i) *= lhs;

	return Vector<T>(resultData);
}

template <class T>
Vector<T> operator/ (const T& lhs, const Vector<T>& rhs)
{
	// Perform scalar multiplication.
	//std::vector<T> resultData;
	//for (int i=0; i<rhs.m_nDims; ++i)
	//	resultData.push_back(lhs * rhs.m_VData.at(i))
	std::vector<T> resultData(rhs._VData);
	for (int i = 0; i < rhs._nDims; ++i)
		resultData.at(i) = lhs / resultData.at(i);

	return Vector<T>(resultData);
}

template<class T>
Vector<T> operator!(const Vector<T>& rhs)
{
	Vector<T> result{ rhs };
	result.Normalize();
	return result;
}

template <class T>
Vector<T> operator^ (const Vector<T>& lhs, const Vector<T>& rhs)
{
	return Vector<T>::cross(lhs, rhs);
}

template <class T>
Vector<T> operator- (const Vector<T>& rhs)
{
	return -1.0*rhs;
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
		cumulativeSum += a._VData.at(i) * b._VData.at(i);

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
	std::vector<T> resultData(3);
	resultData.at(0) = a._VData.at(1) * b._VData.at(2) - a._VData.at(2) * b._VData.at(1);
	resultData.at(1) = -a._VData.at(0) * b._VData.at(2) - a._VData.at(2) * b._VData.at(0);
	resultData.at(2) = a._VData.at(0) * b._VData.at(1) - a._VData.at(1) * b._VData.at(0);

	return Vector<T>(resultData);
}



#endif
