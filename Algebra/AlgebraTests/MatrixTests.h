/* *************************************************************************************************

	qbMatrixTest

	Code to test the basic functionality of the qbMatrix class contained in Matrix.h

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

#include "../Matrix.h"


using namespace std;


namespace AlgebraTests
{
	inline int MatrixTests()
	{
		cout << "Code to test Matrix" << endl;

		// *******************************************************************
		// Create an instance of the Matrix class.
		// This will contain a simple 2D 3x4 matrix
		double simpleData[12] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
		Matrix<double> testMatrix(3, 4, simpleData);

		// Extract and print the elements of testMatrix.
		cout << endl << "**************************" << endl;
		cout << "3x4 matrix test (testMatrix)." << testMatrix << endl;

		// *******************************************************************
		// Test element retrieval.
		cout << endl << "**************************" << endl;
		cout << "Test element retrieval." << endl;
		cout << "Element (0,0) = " << testMatrix.GetElement(0, 0) << endl;
		cout << "Element (1,0) = " << testMatrix.GetElement(1, 0) << endl;
		cout << "Element (2,0) = " << testMatrix.GetElement(2, 0) << endl;
		cout << "Element (0,1) = " << testMatrix.GetElement(0, 1) << endl;
		cout << "Element (1,1) = " << testMatrix.GetElement(1, 1) << endl;
		cout << "Element (2,1) = " << testMatrix.GetElement(2, 1) << endl;
		cout << "Element (5,5) = " << testMatrix.GetElement(5, 5) << endl;

		// *******************************************************************
		// Test matrix multiplication.
		cout << endl << "**************************" << endl;
		cout << "Test matrix multiplication." << endl;
		double simpleData2[12] = { 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0 };
		Matrix<double> testMatrix2(4, 3, simpleData2);
		cout << "4x3 matrix (testMatrix2)" << endl;
		testMatrix2.Print();
		cout << "Multiplication (testMatrix * testMatrix2) result:" << endl;
		Matrix<double> multTest1 = testMatrix * testMatrix2;
		multTest1.Print();

		Matrix<double> multTest2 = testMatrix2 * testMatrix;
		cout << endl << "**************************" << endl
			<< "testMatrix2 * testMatrix:" << multTest2;

		double columnData[3] = { 1.5, 2.5, 3.5 };
		double squareData[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
		Matrix<double> testColumn(3, 1, columnData);
		Matrix<double> squareMatrix(3, 3, squareData);
		cout << endl << "**************************" << endl
			<< "Test multiplication of column vector by matrix." << endl
			<< "Column vector = " << endl << testColumn << endl
			<< "Square matrix = " << endl << squareMatrix << endl
			<< "Column vector * Square matrix = " << endl << (testColumn * squareMatrix)
			<< "Square matrix * Column vector = " << endl << (squareMatrix * testColumn);
		Matrix<double> squareMatrix2 = squareMatrix + 1.0;
		cout << "Square matrix + 1.0 = " << endl << squareMatrix2 << endl
			<< "(Square matrix + 1.0) * Column vector = " << endl << (squareMatrix2 * testColumn);

		// *******************************************************************
		// Test equality operator
		cout << endl << "**************************" << endl;
		cout << "Test equility operator." << endl;
		cout << "testMatrix == testMatrix2: " << (testMatrix == testMatrix2) << endl;
		cout << "testMatrix2 == testMatrix: " << (testMatrix2 == testMatrix) << endl;
		cout << "(Let testMatrix3 = testMatrix)" << endl;
		Matrix<double> testMatrix3 = testMatrix;
		cout << "testMatrix == testMatrix3: " << (testMatrix == testMatrix3) << endl;
		cout << "testMatrix3 == testMatrix: " << (testMatrix3 == testMatrix) << endl;

		// *******************************************************************
		// Test matrix addition by scaler.
		cout << endl << "**************************" << endl;
		cout << "Test addition by scaler" << endl;
		cout << "testMatrix + 2.0 = " << endl << (testMatrix + 2.0) << endl;
		cout << "2.0 + testMatrix = " << endl << (2.0 + testMatrix);

		// *******************************************************************
		// Test matrix subtraction by scaler.
		cout << endl << "**************************" << endl
			<< "Test addition by scaler" << endl
			<< "testMatrix - 2.0 = " << (testMatrix - 2.0) << endl
			<< "2.0 - testMatrix = " << endl << (2.0 - testMatrix);

		// *******************************************************************
		// Test matrix multiplication by scaler.
		cout << endl << "**************************" << endl;
		cout << "Test multiplication by scaler" << endl;
		cout << "testMatrix * 2.0 = " << (testMatrix * 2.0) << endl;
		cout << "2.0 * testMatrix = " << endl << (2.0 * testMatrix);

		// *******************************************************************
		// Test formation of identity matrix.
		Matrix<double> identityTest(5, 5);
		identityTest.SetToIdentity();
		cout << endl << "**************************" << endl
			<< "Test formation of identity matrix." << endl << identityTest;

		// *******************************************************************
		// Test joining of two matrices.
		cout << endl << "**************************" << endl;
		cout << "Test joining of two matrices." << endl;
		Matrix<double> bigSquare(5, 5);
		bigSquare.Join(identityTest);
		cout << bigSquare;

		// *******************************************************************
		// Test matrix inversion
		cout << endl << "**************************" << endl
			<< "Test matrix inversion" << endl
			<< "Attempt to invert a non-square matrix:" << endl;
		try
		{
			testMatrix.Inverse();
		}
		catch (invalid_argument& e)
		{
			cerr << e.what() << endl;
			cout << "Execution would normally stop here with a return code of -1." << endl;
		}

		//double invertTestData[9] = {2.0, 1.0, 1.0, 1.0, 2.0, 3.0, 0.0, 3.0, 1.0};
		double invertTestData[9] = { 2.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 3.0, 1.0 };
		Matrix<double> invertTest(3, 3, invertTestData);
		Matrix<double> invertResult = invertTest;
		invertResult.Inverse();
		cout << endl << "**************************" << endl
			<< "Test matrix inversion" << endl
			<< "Attempt to invert a square matrix:" << endl
			<< "From:" << endl << invertTest << endl
			<< "To:" << endl << invertResult;

		// *******************************************************************
		// Test inversion of a bigger matrix.
		double invertTestData2[25] =
		{ 2.0, 3.0, 4.0, 5.0, 6.0,
		 1.0, 2.0, 3.0, 4.0, 5.0,
		 9.0, 5.0, 3.0, 2.0, 6.0,
		 2.0, 4.0, 6.0, 5.0, 1.0,
		 1.0, 7.0, 5.0, 2.0, 3.0 };
		Matrix<double> invertTest2(5, 5, invertTestData2);
		Matrix<double> invertResult2 = invertTest2;
		invertResult2.Inverse();
		cout << endl << "**************************" << endl
			<< "Test inversion of a bigger matrix." << endl
			<< "From:" << endl << invertTest2 << endl
			<< "To:" << endl << invertResult2;

		Matrix<double> invertAccuracy3 = invertTest2 * invertResult2;
		Matrix<double> invertAccuracy = invertTest * invertResult;
		cout << endl << "**************************" << endl
			<< "Test multiplication of matrix by it's inverse." << endl
			<< "Using invertTest2 * invertResult2:" << endl << invertAccuracy3
			<< "Using invertTest * invertResult:" << endl << invertAccuracy;

		// *******************************************************************
		// Test inversion of a singular matrix.
			/*cout << endl << "**************************" << endl;
			cout << "Test inversion of a singular matrix." << endl;
			double invertTestData3[9] =
				{1.0, 1.0, 1.0,
				 0.0, 1.0, 0.0,
				 1.0, 0.0, 1.0};
			Matrix<double> invertTest3(3, 3, invertTestData3);
			Matrix<double> invertResult3 = invertTest3;
			invertResult3.Inverse();
			cout << "From:" << endl;
			PrintMatrix(invertTest3);
			cout << "To:" << endl;
			PrintMatrix(invertResult3);		*/

		return 0;
	}
}