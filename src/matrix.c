#include "matrix.h"
#include <stddef.h>

void matrix_multiply(Matrix3 res, const Matrix3 A, const Matrix3 B)
{
	for (size_t i = 0; i < MATRIX_DIM; i++) {
		const double *a = A[i];
		for (size_t j = 0; j < MATRIX_DIM; j++) {
			res[i][j] = a[0] * B[0][j] + a[1] * B[1][j] +
				    a[2] * B[2][j];
		}
	}
}

void matrix_multiply_vector(Vector3 res, const Matrix3 M, const Vector3 v)
{
	for (size_t i = 0; i < MATRIX_DIM; i++) {
		const double *m = M[i];
		res[i] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2];
	}
}
