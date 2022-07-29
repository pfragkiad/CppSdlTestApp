/* *************************************************************************************************

	TestCode_qbEIG

	  Code to test the eigenvector and eigenvalue code.

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
#include <fstream>

#include "../Matrix.h"
#include "../Vector.h"
#include "../EIG.h"


using namespace std;


namespace AlgebraTests {
	inline int EIGTests()
	{
		cout << "**********************************************" << endl;
		cout << "Testing eigenvalue and eigenvector code." << endl;
		cout << "Power Iteration Method." << endl;
		cout << "**********************************************" << endl;
		cout << endl;

		{
			cout << "Testing with simple 3x3 matrix:" << endl;

			//std::vector<double> simpleData = {1.0, 2.0, 3.0, 4.0};
			//Matrix<double> testMatrix(2, 2, simpleData);

			std::vector<double> simpleData = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
			Matrix<double> testMatrix(3, 3, simpleData);
			double eigenValue;
			Vector<double> eigenVector;
			EigPIt<double>(testMatrix, eigenValue, eigenVector);

			cout << testMatrix << endl
				<< "Computing eigenvector and eigenvalue..." << endl
				<< "Eigenvector: " << endl << eigenVector
				<< "Eigenvalue = " << eigenValue << "." << endl << endl;
		}

		cout << "**********************************************" << endl
			<< "Testing eigenvalue and eigenvector code." << endl
			<< "Inverse-Power Iteration Method." << endl
			<< "**********************************************" << endl << endl;

		{
			std::vector<double> simpleData = { 0.5, 0.75, 0.5, 1.0, 0.5, 0.75, 0.25, 0.25, 0.25 };
			Matrix<double> testMatrix(3, 3, simpleData);
			cout << "Testing with a simple 3x3 matrix:" << endl << testMatrix << endl;

			// Define the eigenvalues.
			std::vector<double> eigenValues{ 1.5962551, -0.37253087, 0.02627577 };

			// Setup a vector for the eigenvector.
			Vector<double> eigenVector(3);

			// Loop through each eigenvalue.
			for (auto currentValue : eigenValues)
			{
				cout << "Estimated eigenvector for eigenvalue " << currentValue << " = " << endl;
				int returnStatus = InvPIt<double>(testMatrix, currentValue, eigenVector);
				cout << eigenVector;

				if (returnStatus == EIG_MAXITERATIONSEXCEEDED)
					cout << "*** Maximum iterations exceeded ***" << endl;

				cout << endl;
			}

		}

		cout << "**********************************************" << endl
			<< "Testing eigenvalue and eigenvector code." << endl
			<< "New IsSymmetric() function in Matrix class." << endl
			<< "**********************************************" << endl << endl;

		{
			std::vector<double> simpleData = { 4.0, -7.0, 6.0, -7.0, -2.0, 13.0, 6.0, 13.0, 5.0 };
			Matrix<double> testMatrix(3, 3, simpleData);
			cout << "Testing with a simple symmetric matrix." << endl << testMatrix << endl
				<< "Matrix is symmetric: " << (testMatrix.IsSymmetric() ? "True." : "False.") << endl;
		}

		{
			std::vector<double> simpleData = { 4.0, -7.0, 6.0, 7.0, -2.0, 13.0, 6.0, 13.0, 5.0 };
			Matrix<double> testMatrix(3, 3, simpleData);
			cout << "Testing with a simple non-symmetric matrix." << endl << testMatrix << endl;

			cout << "Matrix is symmetric: " << (testMatrix.IsSymmetric() ? "True." : "False.") << endl;
		}

		cout << endl << endl
			<< "**********************************************" << endl
			<< "Testing eigenvalue and eigenvector code." << endl
			<< "Eigenvalues by QR decomposition." << endl
			<< "**********************************************" << endl << endl;

		{
			std::vector<double> simpleData = { 0.5, 0.75, 0.5, 1.0, 0.5, 0.75, 0.25, 0.25, 0.25 };
			Matrix<double> testMatrix(3, 3, simpleData);
			cout << "Testing with a simple (non-symmetric) 3x3 matrix:" << endl << testMatrix << endl;

			// Compute the eigenvalues.
			std::vector<double> eigenValues;
			int returnStatus = EigQR(testMatrix, eigenValues);

			if (returnStatus == EIG_MAXITERATIONSEXCEEDED)
				cout << ">>> Maximum iterations exceeded <<<" << endl;
			else if (returnStatus == EIG_MATRIXNOTSYMMETRIC)
				cout << ">>> Matrix not symmetric. <<<" << endl;

			// Display the eigenvalues.
			cout << "The estimated eigenvalues are:" << endl;
			for (auto currentValue : eigenValues)
				cout << std::setprecision(6) << currentValue << " ";

			cout << endl << endl;
		}

		{
			std::vector<double> simpleData = { 6.0, 5.5, -1.0, 5.5, 1.0, -2.0, -1.0, -2.0, -3.0 };
			Matrix<double> testMatrix(3, 3, simpleData);
			cout << "Testing with a simple (symmetric) 3x3 matrix:" << endl << testMatrix << endl;

			// Compute the eigenvalues.
			std::vector<double> eigenValues;
			int returnStatus = EigQR(testMatrix, eigenValues);

			if (returnStatus == EIG_MAXITERATIONSEXCEEDED)
				cout << ">>> Maximum iterations exceeded <<<" << endl;
			else if (returnStatus == EIG_MATRIXNOTSYMMETRIC)
				cout << ">>> Matrix not symmetric. <<<" << endl;

			// Display the eigenvalues.
			cout << "The estimated eigenvalues are:" << endl;
			for (auto currentValue : eigenValues)
				cout << std::setprecision(6) << currentValue << " ";

			cout << endl << endl;

			// Setup a vector for the eigenvector.
			Vector<double> eigenVector(3);

			// Loop through each eigenvalue.
			for (auto currentValue : eigenValues)
			{
				cout << "Estimated eigenvector for eigenvalue " << currentValue << " = " << endl;
				int returnStatus = InvPIt<double>(testMatrix, currentValue, eigenVector);
				cout << eigenVector;

				if (returnStatus == EIG_MAXITERATIONSEXCEEDED)
					cout << "*** Maximum iterations exceeded ***" << endl;

				cout << endl;
			}

			cout << endl << endl;
		}

		{
			std::vector<double> simpleData = { 4.0, -6.0, 8.0, 7.0, 9.0, -5.0, 9.0, -6.0, -4.0 };
			Matrix<double> testMatrix(3, 3, simpleData);
			cout << "Testing with an example that should have complex eigenvalues:" << endl << testMatrix << endl;

			// Compute the eigenvalues.
			std::vector<double> eigenValues;
			int returnStatus = EigQR(testMatrix, eigenValues);

			if (returnStatus == EIG_MATRIXNOTSYMMETRIC)
				cout << ">>> Matrix not symmetric. <<<" << endl;
			else if (returnStatus == EIG_MAXITERATIONSEXCEEDED)
				cout << ">>> Maximum iterations exceeded <<<" << endl;

			// Display the eigenvalues.
			cout << "The estimated eigenvalues are:" << endl;
			for (auto currentValue : eigenValues)
				cout << std::setprecision(6) << currentValue << " ";

			cout << endl << endl;

			// Setup a vector for the eigenvector.
			Vector<double> eigenVector(3);

			// Loop through each eigenvalue.
			for (auto currentValue : eigenValues)
			{
				cout << "Estimated eigenvector for eigenvalue " << currentValue << " = " << endl;
				int returnStatus = InvPIt<double>(testMatrix, currentValue, eigenVector);
				cout << eigenVector;

				if (returnStatus == EIG_MAXITERATIONSEXCEEDED)
					cout << "*** Maximum iterations exceeded ***" << endl;

				cout << endl;
			}

			cout << endl << endl;
		}

		return 0;
	}
}