// NOTE: This file is just for quick testing

#include "cielo.h"
#include "matrix.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
	// rgb_validate_hex {{{
	const char red[] = "#EE4B2B";
	bool valid_red = rgb_validate_hex(red);
	printf("Hex code for red  is %s\n", valid_red ? "VALID" : "INVALID");

	const char lime[] = "32cd32";
	bool valid_lime = rgb_validate_hex(lime);
	printf("Hex code for lime is %s\n", valid_lime ? "VALID" : "INVALID");
	// }}}

	// rgb_from_hex {{{
	bool ok = false;
	Rgb plum = rgb_from_hex("#dda0dd", &ok);

	assert(ok);
	assert(lround(plum.r * 255.0) == 221);
	assert(lround(plum.g * 255.0) == 160);
	assert(lround(plum.b * 255.0) == 221);

	printf("Plum: Red   -> %.4f\n", plum.r); // 0.8667
	printf("Plum: Green -> %.4f\n", plum.g); // 0.6275
	printf("Plum: Blue  -> %.4f\n", plum.b); // 0.8667

	// }}}

	// matrix_multiply {{{
	const Matrix3 A = {{0.814, 0.223, 0.705},
			   {0.612, 0.951, 0.137},
			   {0.469, 0.388, 0.995}};
	const Matrix3 B = {{0.427, 0.913, 0.286},
			   {0.731, 0.124, 0.859},
			   {0.552, 0.678, 0.391}};

	Matrix3 C;
	matrix_multiply(C, A, B); // C = A * B

	// Expected result:
	// C = {{0.899751, 1.24882, 0.700016},
	//      {1.03213, 0.769566, 1.04551},
	//      {1.03313, 1.15092, 0.856471}}

	printf("C[0][1] = %.5f\n", C[0][1]);
	printf("C[1][2] = %.5f\n", C[1][2]);
	printf("C[2][0] = %.5f\n", C[2][0]);
	// }}}

	return 0;
}

// vim: foldmethod=marker
