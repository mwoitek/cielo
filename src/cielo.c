#include "cielo.h"
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

const size_t RGB_HEX_LENGTH = 7;

// TODO: remove
float cube(float x) { return powf(x, 3.0F); }

bool rgb_validate_hex(const char *hex)
{
	if (!hex || *hex != '#' || !memchr(hex, '\0', RGB_HEX_LENGTH + 1) ||
	    strlen(hex) < RGB_HEX_LENGTH) {
		return false;
	}

	for (size_t i = 1; i < RGB_HEX_LENGTH; i++) {
		if (!isxdigit(hex[i])) {
			return false;
		}
	}

	return true;
}

Rgb rgb_from_hex(const char *hex, bool *ok)
{
	Rgb rgb = {0.0, 0.0, 0.0};

	if (!rgb_validate_hex(hex)) {
		*ok = false;
		return rgb;
	}

	char *hex_slice = "00";
	unsigned long chans[3] = {0, 0, 0};

	for (size_t i = 0; i < 3; i++) {
		memcpy(hex_slice, hex + 2 * i + 1, 2);
		chans[i] = strtoul(hex_slice, NULL, 16);
	}

	rgb.r = (double)chans[0] / 255.0;
	rgb.g = (double)chans[1] / 255.0;
	rgb.b = (double)chans[2] / 255.0;

	*ok = true;
	return rgb;
}
