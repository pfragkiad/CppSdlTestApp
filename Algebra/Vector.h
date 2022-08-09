#ifndef VECTOR_H
#define VECTOR_H

#ifndef MAX_VECTOR_SIZE
#define MAX_VECTOR_SIZE 4
#endif

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm> //fill

template <class T>
class Vector
{
public:
	// Define the various constructors.
	// Default.
	Vector();

	// With a single integer specifying the number of dimensions.
	Vector(size_t size);

	//// Move constructor
	//inline Vector(Vector<T>&& v) noexcept :
	//	_VData(std::move(v._VData)), _size(v._size)
	//{}
	// Copy constructor
	inline Vector(const Vector<T>& v)
	{
		_size = v._size;
		//_VData = new T[_size];
		std::copy(v._VData, v._VData + _size, _VData);
	}
	
	// Copy assignment
	inline Vector& operator=(const Vector<T>& v)
	{
		_size = v._size;
		//_VData = new T[_size];
		std::copy(v._VData, v._VData + _size, _VData);
		return *this;
	}

	//// Move assigment (NEEDED OR COMPILATION FAILS)
	//inline Vector& operator =(Vector<T>&& v)
	//{
	//	_size = v._size;
	//	_VData = std::move(v._VData);
	//	return *this;
	//}

	// With input data (std::vector).
	Vector(std::vector<T> data);

	Vector(std::initializer_list<T> data);

	// And the destructor.
	~Vector();

	// Returns the number of the vector elements.
	size_t Count() const;

	// Functions to handle elements of the vector.
	T Get(size_t index) const;
	void Set(size_t index, T value);

	// Functions to perform computations on the vector.
	// Return the length of the vector.
	T Length() const;

	T LengthSquared() const;


	// Return a normalized copy of the vector.
	Vector<T> Normalized() const;

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
	template <class T> friend Vector<T> operator- (const Vector<T>& rhs);
	template <class T> friend Vector<T> operator/ (const T& lhs, const Vector<T>& rhs);

	Vector<T> RotateAround(const Vector<T>& vref, T angle);


	// Static functions.
	static T dot(const Vector<T>& a, const Vector<T>& b);
	static Vector<T> cross(const Vector<T>& a, const Vector<T>& b);

	template <class T> friend std::ostream& operator << (std::ostream& os, const Vector<T>& v);

	void inline Print() const
	{
		for (int row = 0; row < _size; ++row)
			std::cout << _VData[row] << std::endl;
	}

	void inline Print(int precision) const
	{
		for (int row = 0; row < _size; ++row)
			std::cout << std::fixed << std::setprecision(precision) << _VData[row] << std::endl;
	}


private:
	//std::vector<T> _VData;
	//T* _VData = nullptr;
	T _VData[MAX_VECTOR_SIZE];

	size_t _size;
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
	for (size_t row = 0; row < v._size; ++row)
		//os << std::fixed << std::setprecision(6) << v.GetElement(row) << std::endl;
		os << std::fixed << std::setprecision(6) << v._VData[row] << std::endl;
	return os;
}

/* **************************************************************************************************
CONSTRUCTOR / DESTRUCTOR FUNCTIONS
/* *************************************************************************************************/
// The default constructor (default is a vector of 3 dim).
template <class T>
Vector<T>::Vector()
{
	_size = 3;
	//_VData = new T[_size];
	std::fill(_VData, _VData + _size, static_cast<T>(0.0));
	//_VData = std::vector<T>();
}

template <class T>
Vector<T>::Vector(size_t numDims)
{
	_size = numDims;
	//_VData = new T[_size];
	std::fill(_VData, _VData + _size, static_cast<T>(0.0));
}



template <class T>
Vector<T>::Vector(std::vector<T> inputData)
{
	_size = inputData.size();
	//_VData = new T[_size];
	std::copy(inputData.cbegin(), inputData.cend(), _VData);
	//_VData = inputData;
}

template <class T>
Vector<T>::Vector(std::initializer_list<T> data)
{
	_size = data.size();
	//_VData = new T[_size];
	std::copy(data.begin(), data.end(), _VData);
	//_VData = std::vector<T>(data);
}


template <class T>
Vector<T>::~Vector()
{
	//if (_VData != nullptr)
	//	delete[] _VData;
}

/* **************************************************************************************************
FUNCTIONS TO RETURN PARAMETERS
/* *************************************************************************************************/
template <class T>
size_t Vector<T>::Count() const
{
	return _size;
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
T Vector<T>::Length() const
{
	T cumulativeSum = static_cast<T>(0.0);
	for (size_t i = 0; i < _size; ++i)
		cumulativeSum += _VData[i] * _VData[i];

	return sqrt(cumulativeSum);
}


template <class T>
T Vector<T>::LengthSquared() const
{
	T cumulativeSum = static_cast<T>(0.0);
	for (size_t i = 0; i < _size; ++i)
		cumulativeSum += _VData[i] * _VData[i];

	return cumulativeSum;
}



// Return a normalized copy of the vector.
template <class T>
Vector<T> Vector<T>::Normalized() const
{
	// Compute the vector norm.
	//T length = norm();

	//// Compute the normalized version of the vector.
	//Vector<T> result(_VData);
	//return result * (static_cast<T>(1.0) / vecNorm);
	return Vector<T>(_VData) / Length();
}

// Normalize the vector in place.
template <class T>
void Vector<T>::Normalize()
{
	// Compute the vector norm.
	T length = Length();

	// Compute the elements of the normalized version of the vector.
	for (size_t i = 0; i < _size; ++i)
	{
		//T temp = _VData[i] / vecNorm; //;* (static_cast<T>(1.0) / vecNorm);
		//_VData[i] = temp;
		_VData[i] /= length;
	}
}

/* **************************************************************************************************
OVERLOADED OPERATORS
/* *************************************************************************************************/
template <class T>
Vector<T> Vector<T>::operator+ (const Vector<T>& rhs) const
{
	// Check that the number of dimensions match.
	if (_size != rhs._size)
		throw std::invalid_argument("Vector dimensions do not match.");

	//std::vector<T> resultData;
	//for (int i = 0; i < m_size; ++i)
	//	resultData.push_back(m_VData[i] + rhs.m_VData[i]);

	//std::vector<T> resultData(_VData);
	//for (size_t i = 0; i < _size; ++i)
	//	resultData[i] += rhs._VData[i];
	//Vector<T> result(resultData);

	Vector<T> result{ *this };
	for (size_t i = 0; i < _size; ++i)
		result._VData[i] += rhs._VData[i];

	return result;
}

template <class T>
Vector<T> Vector<T>::operator- (const Vector<T>& rhs) const
{
	// Check that the number of dimensions match.
	if (_size != rhs._size)
		throw std::invalid_argument("Vector dimensions do not match.");

	//std::vector<T> resultData;
	//for (int i = 0; i < _size; ++i)
	//	resultData.push_back(_VData[i] - rhs._VData[i]);

	//std::vector<T> resultData(_VData);
	//for (size_t i = 0; i < _size; ++i)
	//	resultData[i] -= rhs._VData[i];
	//Vector<T> result(resultData);

	Vector<T> result{ *this };
	for (size_t i = 0; i < _size; ++i)
		result._VData[i] -= rhs._VData[i];

	return result;
}

template <class T>
Vector<T> Vector<T>::operator* (const T& rhs) const
{
	// Perform scalar multiplication.
	//std::vector<T> resultData;
	//for (int i = 0; i < _size; ++i)
	//	resultData.push_back(_VData[i] * rhs);

	//std::vector<T> resultData(_VData);
	//for (size_t i = 0; i < _size; ++i)
	//	resultData[i] *= rhs;

	Vector<T> result{ *this };
	for (size_t i = 0; i < _size; ++i)
		result._VData[i] *= rhs;
	return result;
}

template <class T>
T Vector<T>::operator*(const Vector<T>& rhs) const //dot product
{
	return dot(*this, rhs);
}

template <class T>
Vector<T> Vector<T>::operator/ (const T& rhs) const
{
	//std::vector<T> resultData(_VData);
	//for (size_t i = 0; i < _size; ++i)
	//	resultData[i] /= rhs;

	//Vector<T> result(resultData);
	//return result;
	//return Vector<T>(resultData);

	Vector<T> result{ *this };
	for (size_t i = 0; i < _size; ++i)
		result._VData[i] /= rhs;
	return result;

}

//mine
template <class T>
void Vector<T>::operator*= (const T& rhs) ///////////
{
	// Perform scalar multiplication.
	for (size_t i = 0; i < _size; ++i)
		_VData[i] *= rhs;
}

template <class T>
void Vector<T>::operator/= (const T& rhs) ///////////
{
	// Perform scalar multiplication.
	for (size_t i = 0; i < _size; ++i)
		_VData[i] /= rhs;
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
	//for (int i=0; i<rhs.m_size; ++i)
	//	resultData.push_back(lhs * rhs.m_VData[i])

	//std::vector<T> resultData(rhs._VData);
	//for (size_t i = 0; i < rhs._size; ++i)
	//	resultData[i] *= lhs;
	//return Vector<T>(resultData);

	Vector<T> result{ rhs };
	for (size_t i = 0; i < rhs._size; ++i)
		result._VData[i] *= lhs;
	return result;

}

template <class T>
Vector<T> operator/ (const T& lhs, const Vector<T>& rhs)
{
	// Perform scalar multiplication.
	//std::vector<T> resultData;
	//for (int i=0; i<rhs.m_size; ++i)
	//	resultData.push_back(lhs * rhs.m_VData[i])

	//std::vector<T> resultData(rhs._VData);
	//for (size_t i = 0; i < rhs._size; ++i)
	//	resultData[i] = lhs / resultData[i];
	//return Vector<T>(resultData);

	Vector<T> result(rhs._size());
	for (size_t i = 0; i < rhs._size; ++i)
		result._VData[i] = lhs / rhs._VData[i];
	return result;

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
	return -1.0 * rhs;
}

template<class T>
inline Vector<T> Vector<T>::RotateAround(const Vector<T>& vref, T angle)
{
	Vector<T> e_vref = !vref;
	Vector<T> projectedOnVRef = dot(*this, e_vref) * e_vref;
	Vector<T> verticalToVRef = *this - projectedOnVRef;

	T verticalToVRefLength = verticalToVRef.Length();

	Vector<T> ex = !verticalToVRef;
	Vector<T> ey = e_vref ^ ex;

	T x = static_cast<T>(verticalToVRefLength * cos(angle));
	T y = static_cast<T>(verticalToVRefLength * sin(angle));

	return x * ex + y * ey + projectedOnVRef;
}

/* **************************************************************************************************
STATIC FUNCTIONS
/* *************************************************************************************************/
template <class T>
T Vector<T>::dot(const Vector<T>& a, const Vector<T>& b)
{
	// Check that the number of dimensions match.
	if (a._size != b._size)
		throw std::invalid_argument("Vector dimensions must match for the dot-product to be computed.");

	// Compute the dot product.
	T cumulativeSum = static_cast<T>(0.0);
	for (size_t i = 0; i < a._size; ++i)
		cumulativeSum += a._VData[i] * b._VData[i];

	return cumulativeSum;
}

template <class T>
Vector<T> Vector<T>::cross(const Vector<T>& a, const Vector<T>& b)
{
	if (a._size != b._size)
		throw std::invalid_argument("Vector dimensions must match for the cross-product to be computed.");

	if (a._size != 3)
		throw std::invalid_argument("The cross-product can only be computed for three-dimensional vectors.");

	// Compute the cross product.
	T a0 = a._VData[1] * b._VData[2] - a._VData[2] * b._VData[1];
	T a1 = -a._VData[0] * b._VData[2] + a._VData[2] * b._VData[0];
	T a2 = a._VData[0] * b._VData[1] - a._VData[1] * b._VData[0];

	return Vector<T>({ a0,a1,a2 });
}



#endif
