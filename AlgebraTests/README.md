# qbLinAlg
Linear algebra library for C++, created to accompany the corresponding series of videos on the QuantitativeBytes YouTube channel at:

www.youtube.com/c/QuantitativeBytes.

Many excellent linear algebra libraries already exist for C++ and as such this code is intended to be primarily for educational purposes, rather than as an alternative to those. It is intended to be studied alongside the corresponding series of videos on the QuantitativeBytes YouTube channel, the full playlist for which can be found here:

https://www.youtube.com/playlist?list=PL3WoIG-PLjSv9vFx2dg0BqzDZH_6qzF8-

As this code is paired with the corresponding videos on the QuantitativeBytes YouTube channel, pull requests will not be accepted.

## Specific functions

### PCA.h

Implementation of Principal Component Analysis (PCA).

https://youtu.be/ifxUSa5r_Ls

### QR.h

Function to perform QR decomposition on the given matrix, returning an orthogonal matrix, Q, and an upper-triangular matrix, R. Uses the method of Householder reflections to perform the decomposition.

https://youtu.be/MR54VHqhROw

### EIG.h

Functions for computing the eigenvectors and eigenvalues for a given matrix. Contains an implementation of the power iteration method for computing the dominant eigenvector, the inverse-power-iteration method and an implementation of the QR algorithm to estimate eigenvalue / eigenvector pairs for a given symmetric matrix.

https://youtu.be/hnLyWa2_hd8

https://youtu.be/tYqOrvUOMFc

### qbLinSolve.h

Function for solving systems of linear equations. Uses an implementation of Gaussian elimination and back-substitution.

https://youtu.be/GKkUU4T6o08

https://youtu.be/NJIv0xH-S0I

https://youtu.be/KsrlAnEmRNE

### LSQ.h

Function for computing the linear least squares solution to an over-determined system of linear equations.

https://youtu.be/4UVPXs3vIHk

https://youtu.be/fG1JXf7WSQw

### Matrix.h

Class for handling matrices. Implements a number of useful functions:

#### qbMatrix - Inverse()

Compute the inverse of the matrix using the Gauss-Jordan elimination method.

https://youtu.be/wOlG_fnd3v8

https://youtu.be/AEuNHdgn-R8

https://youtu.be/JWM8Y8b1ZVQ

#### qbMatrix - RowEchelon()

Convert the matrix to row echelon form.

#### qbMatrix - Transpose()

Transpose the matrix.

#### qbMatrix - Determinant()

Compute the determinant of the matrix.

https://youtu.be/YVk0nYrwBb0

### Vector.h

Class for handling vectors. Implements a number of useful functions:

https://youtu.be/YfWX-EsvX7c

https://youtu.be/c5AB5T7LBCI

#### Vector - Normalized()

Returns a normalized copy of the vector.

#### Vector - Normalize()

Normalizes the vector 'in-place'.

#### Vector - dot()

Computes the vector dot product.

#### Vector - cross()

Computes the vector cross product.
