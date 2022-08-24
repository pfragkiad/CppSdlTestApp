/* *************************************************************************************************

	TestCode_qbLinearSolve

	 Code to test solving systems of linear equations using the qbLinearSolve function. Also tests
	computation of the matrix rank in situations where Gaussian eliminiation is possible and also
	where it is not.

	*** INPUTS ***

	None

	*** OUTPUTS ***

	INT				Flag indicating success or failure of the process.

	Created as part of the qbLinAlg linear algebra library, which is intended to be primarily for
	educational purposes. For more details, see the corresponding videos on the QuantitativeBytes
	YouTube channel at:

	www.youtube.com/c/QuantitativeBytes

	************************************************************************************************* */
#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>
#include <string>
#include <sstream>
#include <vector>
#include <random>

#include "../Matrix.h"
#include "../Vector.h"
#include "../LinSolve.h"

using namespace std;

namespace AlgebraTests
{
	inline int LinearSolveTests()
	{
		cout << "Code to test Matrix" << endl;
		cout << "Testing conversion of matrix to row echelon form." << endl;
		cout << endl;

		// Generate a matrix to test things with.
		std::vector<double> simpleData = { 1.0, 3.0, -1.0, 13.0, 4.0, -1.0, 1.0, 9.0, 2.0, 4.0, 3.0, -6.0 };
		Matrix<double> testMatrix(3, 4, simpleData);

		cout << "Original matrix:" << endl << testMatrix << endl;

		// Convert to row echelon form.
		Matrix<double> rowEchelonMatrix = testMatrix.RowEchelon();

		cout << "Converted to row echelon form:" << endl << rowEchelonMatrix << endl;

		// Define another matrix as the first part of our system of linear equations.
		std::vector<double> simpleData2 = { 1.0, 3.0, -1.0, 4.0, -1.0, 1.0, 2.0, 4.0, 3.0 };
		Matrix<double> aMat(3, 3, simpleData2);
		cout << "We setup the equations in the form of Ax = b, where A = " << endl << aMat << endl;

		// Define a vector to hold the RHS of our system of linear equations.
		std::vector<double> VData{ 13.0, 9.0, -6.0 };
		Vector<double> bVec{ VData };
		cout << "And b = " << endl << bVec << endl;

		// Call the qbLinSolve function.
		Vector<double> testResult(3);
		int test = LinSolve<double>(aMat, bVec, testResult);
		cout << "And the final result is:" << endl << testResult << endl;

		// ***************************************************************************************************
		// Try some random tests.
		std::random_device myRandomDevice;
		std::mt19937 myRandomGenerator(myRandomDevice());
		std::uniform_real_distribution<double> myDistribution(-25.0, 25.0);

		int numUnknowns = 10;

		std::vector<double> coefficientData;
		std::vector<double> unknownData;
		// Populate the coefficient data.
		for (int i = 0; i < (numUnknowns * numUnknowns); ++i)
		{
			double randomNumber = myDistribution(myRandomGenerator);
			coefficientData.push_back(randomNumber);
		}
		Matrix<double> coefficientMatrix(numUnknowns, numUnknowns, coefficientData);
		cout << "A random coefficient matrix = " << endl << coefficientMatrix << endl;

		cout << "And the random unknown values = " << endl;
		for (int i = 0; i < numUnknowns; ++i)
		{
			double randomNumber = myDistribution(myRandomGenerator);
			unknownData.push_back(randomNumber);
		}
		Vector<double> unknownVector{ unknownData };
		unknownVector.Print(", ");
		cout << endl;

		cout << "Compute the equation results = " << endl;
		Vector<double> systemResult = coefficientMatrix * unknownVector;
		cout << systemResult << endl;

		cout << "Attempt to solve the linear system..." << endl;
		Vector<double> compSolution(numUnknowns);
		int compTest = LinSolve<double>(coefficientMatrix, systemResult, compSolution);
		cout << compSolution << endl;

		cout << "And compare the actual result with the computed solution..." << endl;
		Vector<double> errorVector = unknownVector - compSolution;
		cout << errorVector << endl;

		// ***************************************************************************************************
		// Test computation of the matrix rank.
		Matrix<double> aMatRowEchelon = aMat.RowEchelon();
		cout << "***************************************************************" << endl
			<< "Testing computation of matrix rank" << endl
			<< "***************************************************************" << endl
			<< endl
			<< "Testing with a solvable system:" << endl << aMat
			<< "Rank = " << aMat.Rank() << endl
			<< endl
			<< "Row echelon form:" << endl << aMatRowEchelon << endl;

		// Test the condition when Gaussian elmination fails.
		std::vector<double> geFailData = { 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0 };
		Matrix<double> geFailMatrix(3, 3, geFailData);
		Matrix<double> geFailResult = geFailMatrix.RowEchelon();
		cout << "***************************************************************" << endl
			<< "Testing the condition when Gaussian elimination fails" << endl
			<< "***************************************************************" << endl
			<< "Testing with:" << endl << geFailMatrix << endl
			<< "Attempt to perform Gaussian elimination on this gives:" << endl
			<< geFailResult << endl
			<< "Attempt to compute the rank gives:" << endl
			<< "Rank = " << geFailMatrix.Rank() << endl << endl
			<< "Testing with a zero matrix:" << endl;

		std::vector<double> geFailData2 = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
		Matrix<double> geFailMatrix2(3, 3, geFailData2);
		cout << geFailMatrix2 << endl
			<< "Rank = " << geFailMatrix2.Rank() << endl << endl
			<< "Testing with a larger example:" << endl << coefficientMatrix << endl
			<< "The rank is " << coefficientMatrix.Rank() << endl << endl;

		std::vector<double> geFailData3 = { 1.0, 2.0, 3.0, 4.0, 4.0, 3.0, 2.0, 1.0, 2.0, 4.0, 6.0, 8.0, 8.0, 6.0, 4.0, 2.0 };
		Matrix<double> geFailMatrix3(4, 4, geFailData3);
		cout << "Testing with 4x4:" << endl << endl << geFailMatrix3
			<< "Rank = " << geFailMatrix3.Rank() << endl << endl;

		// Test the two possible conditions with no solution
		cout << "***************************************************************" << endl;
		cout << "Testing the two possible conditions with no solution" << endl;
		cout << "***************************************************************" << endl;
		cout << endl;
		{
			// Setup a system with an infinite number of solutions.
			cout << "A system with an infinite number of solutions:" << endl;
			std::vector<double> aMatData = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0 };
			std::vector<double> bVecData = { 0.0, 0.0, 0.0 };
			Matrix<double> aMat(3, 3, aMatData);
			Vector<double> bVec{ bVecData };
			Vector<double> solution(3);
			int test = LinSolve<double>(aMat, bVec, solution);
			if (test > 0)
				cout << solution;
			else
				cout << "Error condition: " << test << endl;
		}
		cout << endl;
		{
			// Setup a system with no solutions.
			cout << "A system with no solutions:" << endl;
			std::vector<double> aMatData = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
			std::vector<double> bVecData = { 0.0, -1.0, 1.0 };
			Matrix<double> aMat(3, 3, aMatData);
			Vector<double> bVec{ bVecData };
			Vector<double> solution(3);
			int test = LinSolve<double>(aMat, bVec, solution);
			if (test > 0)
				cout << solution;
			else
				cout << "Error condition: " << test << endl;
		}

		return 0;
	}
}