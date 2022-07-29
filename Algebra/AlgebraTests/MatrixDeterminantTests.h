/* *************************************************************************************************

	qbMatrix_DeterminantTest
	
	Code to test computation of the determinant using the Matrix class.
	
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
#include <fstream>

#include "../Matrix.h"

using namespace std;

namespace AlgebraTests
{
	inline int MatrixDeterminantTests()
	{
		cout << "Testing implementation of determinant calculation." << endl;
		cout << endl;

		cout << "Generate a test matrix." << endl;
		double testData[9] = { 2.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 3.0, 1.0 };
		Matrix<double> testMatrix(3, 3, testData);
		cout << testMatrix << endl;

		cout << "Extract sub-matrix for element (0,0)" << endl;
		cout << testMatrix.FindSubMatrix(0, 0) << endl;

		cout << "Extract sub-matrix for element (0,1)" << endl;
		cout << testMatrix.FindSubMatrix(0, 1) <<endl;

		cout << "Extract sub-matrix for element (0,2)" << endl;
		cout << testMatrix.FindSubMatrix(0, 2) << endl;

		cout << "Extract sub-matrix for element (1,1)" << endl;
		cout << testMatrix.FindSubMatrix(1, 1) << endl;

		cout << "Test with a larger matrix." << endl;
		double testData2[25] =
		{ 2.0, 3.0, 4.0, 5.0, 6.0,
		 1.0, 2.0, 3.0, 4.0, 5.0,
		 9.0, 5.0, 3.0, 2.0, 6.0,
		 2.0, 4.0, 6.0, 5.0, 1.0,
		 1.0, 7.0, 5.0, 2.0, 3.0 };
		Matrix<double> testMatrix2(5, 5, testData2);
		cout << testMatrix2 <<endl;

		cout << "Extract sub-matrix for element (0,0)" << endl;
		Matrix<double> minor5 = testMatrix2.FindSubMatrix(0, 0);
		cout << minor5 << endl;

		cout << "Extract sub-matrix for element (0,1)" << endl;
		cout << testMatrix2.FindSubMatrix(0, 1) << endl;

		cout << "Extract sub-matrix for element (0,2)" << endl;
		cout << testMatrix2.FindSubMatrix(0, 2) << endl;

		cout << "Extract sub-matrix for element (1,1)" << endl;
		cout << testMatrix2.FindSubMatrix(1, 1) << endl;

		cout << "Test determinant of 3x3 matrix:" << endl;
		cout << testMatrix.Determinant() << endl;

		cout << "Test determinant of 5x5 matrix:" << endl;
		cout << testMatrix2.Determinant() << endl;

		cout << "Test determinant of a singular matrix:" << endl;
		double testData3[9] =
		{ 1.0, 1.0, 1.0,
		 0.0, 1.0, 0.0,
		 1.0, 0.0, 1.0 };
		Matrix<double> testMatrix3(3, 3, testData3);
		cout << testMatrix3 << endl << "Determinant = " << testMatrix3.Determinant() << endl;

		return 0;
	}
}
