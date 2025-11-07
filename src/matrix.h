#ifndef __MATRIX_H__
#define __MATRIX_H__

#define MATRIX_DIM 3

typedef double Matrix3[MATRIX_DIM][MATRIX_DIM];
typedef double Vector3[MATRIX_DIM];

void matrix_multiply(Matrix3 res, const Matrix3 A, const Matrix3 B);
void matrix_multiply_vector(Vector3 res, const Matrix3 M, const Vector3 v);

#endif
