// NOTE: This file is just for quick testing

#include "cielo.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
	// rgb_validate_hex {{{
	char red[] = "#EE4B2B";
	bool valid_red = rgb_validate_hex(red);
	printf("Hex code for red  is %s\n", valid_red ? "VALID" : "INVALID");

	char lime[] = "32cd32";
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

	return 0;
}

// vim: foldmethod=marker
