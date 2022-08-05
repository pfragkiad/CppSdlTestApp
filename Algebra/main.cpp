// AlgebraTests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "../Algebra/Algebra.h"


#include <iostream>
#include <vector>


int main()
{
	//AlgebraTests::MDeterminantTests();
	//AlgebraTests::EIGTests();
	//AlgebraTests::LinearSolveTests();
	//AlgebraTests::LSQTests(); //problematic
	//AlgebraTests::MatrixTests();
	//AlgebraTests::PCATests();
	//AlgebraTests::QRTests();

	//Vector<double> v1(std::vector<double>({ 0.0,1.0,3.0 }));
	Vector<double> v1({ 1.0,0.0,0.0 }), v1t({ 0.0,1.0,0.0 });
	double vn = v1 * v1t; //dot product

	std::cout << (v1 ^ v1t) << std::endl;
	//std::cout << n << std::endl;
   // std::cout << vn << std::endl;

	double simpleData[12] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
	Matrix<double> testMatrix(3, 4, simpleData);
	std::cout << "3x4 matrix test (testMatrix)." << std::endl << testMatrix << std::endl;


	std::vector<double> v2{ 1.0,1.0 };
	std::vector<double> v3(v2);
	v3.at(0) = 8.0;

	std::cout << v2.at(0) << std::endl;
}
