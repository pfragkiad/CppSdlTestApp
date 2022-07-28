// AlgebraTests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "../CppSdlTest/algebra/Vector.h"
#include "../CppSdlTest/algebra/Matrix.h"
#include "../CppSdlTest/algebra/EIG.h"
#include "../CppSdlTest/algebra/LinSolve.h"
#include "../CppSdlTest/algebra/LSQ.h"
#include "../CppSdlTest/algebra/PCA.h"
#include "../CppSdlTest/algebra/QR.h"


#include <iostream>
#include <vector>

int main()
{
    Vector<double> v1(std::vector<double>({ 0.0,1.0,3.0 }));

    std::vector<double> v2{ 1.0,1.0 };
    std::vector<double> v3(v2);
    v3.at(0) = 8.0;

    std::cout << v2.at(0) << std::endl;
}
