/* *************************************************************************************************

	TestCode_PCA
	
	  Code to test the principal component analysis functions.
	
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
#include "../PCA.h"

using namespace std;

namespace AlgebraTests
{
	inline void PCATests()
	{
		cout << "**********************************************" << endl;
		cout << "Testing principal component analysis code." << endl;
		cout << "**********************************************" << endl;
		cout << endl;

		{
			cout << "Testing with 100 observations of 3 variables:" << endl;

			// Read data from the .CSV file.
			string rowData;
			string number;
			stringstream rowDataStream;
			std::vector<double> testData;
			int numRows = 0;
			int numCols = 0;
			ifstream inputFile("PCATestData.csv");

			/* If the file open successfully then do stuff. */
			if (inputFile.is_open())
			{
				cout << "Opened file successfully..." << endl;

				while (!inputFile.eof())
				{

					// Read the next line.
					getline(inputFile, rowData);

					// Loop through and extract the individual numbers.
					rowDataStream.clear();
					rowDataStream.str(rowData);

					if (numRows < 1)
						numCols = 0;

					while (rowDataStream.good())
					{
						getline(rowDataStream, number, ',');
						testData.push_back(atof(number.c_str()));

						if (numRows < 1)
							numCols++;
					}
					numRows++;
				}

				// Close the file.
				inputFile.close();

				// For some reason, the above reads one line too many.
				numRows--;
				testData.pop_back();

				cout << "Completed reading file..." << endl;
				cout << "Read " << numRows << " observations of " << numCols << " variables." << endl;
				cout << "Constituting " << testData.size() << " elements in total." << endl;

				// Form into a matrix.
				Matrix<double> X(numRows, numCols, testData);

				// Compute the covariance matrix.
				std::vector<double> columnMeans = PCA::ComputeColumnMeans(X);
				Matrix<double> X2 = X;
				PCA::SubtractColumnMeans(X2, columnMeans);

				Matrix<double> covX = PCA::ComputeCovariance(X2);
				cout << endl  << "Giving the covariance matrix as: " << endl << covX;

				// Compute the eigenvectors.
				Matrix<double> eigenvectors;
				int testResult = PCA::ComputeEigenvectors(covX, eigenvectors);
				cout << endl << "And the eigenvectors as: " << endl << eigenvectors;

				// Test the overall function.
				cout << endl;
				cout << "Testing overall function..." << endl;
				Matrix<double> eigenvectors2;
				int testResult2 = PCA::PCA(X, eigenvectors2);
				cout << "testResult2 = " << testResult2 << endl;
				cout << "And the final eigenvectors are:" << endl << eigenvectors2;

				// Test dimensionality reduction.
				cout << endl;
				cout << "Testing dimensionality reduction." << endl;
				cout << "Starting with X which has " << X.RowsCount() << " rows and " << X.ColsCount() << " columns." << endl;
				cout << endl;
				cout << "Using only the first two principal components:" << endl;
				Matrix<double> V, part2;
				eigenvectors.Separate(V, part2, 2);
				V.Print(8);
				cout << endl;

				Matrix<double> newX = (V.Transpose() * X.Transpose()).Transpose();
				cout << "Result has " << newX.RowsCount() << " rows and " << newX.ColsCount() << " columns." << endl;

				// Open a file for writing
				ofstream outputFile("PCATestData_Reduced.csv");
				if (outputFile.is_open())
				{
					for (int i = 0; i < newX.RowsCount(); ++i)
					{
						outputFile << newX.Get(i, 0) << "," << newX.Get(i, 1) << endl;
					}
					outputFile.close();
				}

			}
		}
	}
}