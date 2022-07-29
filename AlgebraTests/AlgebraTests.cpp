// AlgebraTests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Vector.h"
#include "Matrix.h"
#include "EIG.h"
#include "LinSolve.h"
#include "LSQ.h"
#include "PCA.h"
#include "QR.h"


#include <iostream>
#include <vector>

int main()
{
    //Vector<double> v1(std::vector<double>({ 0.0,1.0,3.0 }));
    Vector<double> v1({ 1.0,0.0,0.0 }), v1t({0.0,1.0,0.0});
    double vn = v1*v1t; //dot product
    auto n = v1 ^ v1t;
    n.Print();
   // std::cout << vn << std::endl;


    std::vector<double> v2{ 1.0,1.0 };
    std::vector<double> v3(v2);
    v3.at(0) = 8.0;

    std::cout << v2.at(0) << std::endl;
}
