// NOTE: This file is just for quick testing

#include "cielo.h"
#include <stdio.h>

int main(void)
{
	char *red = "#EE4B2B";
	bool valid_red = rgb_validate_hex(red);
	printf("Hex code for red is %s\n", valid_red ? "VALID" : "INVALID");
	return 0;
}
