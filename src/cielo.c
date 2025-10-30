#include "cielo.h"
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

const size_t RGB_HEX_LENGTH = 6; // no # at the start

float cube(float x) { return powf(x, 3.0F); }

// NOTE: Normalized channel values will be used
typedef struct {
	double r;
	double g;
	double b;
} Rgb;

Rgb rgb_from_hex(const char *hex, bool *ok)
{
	Rgb rgb = {0.0, 0.0, 0.0};

	if (!hex || !memchr(hex, '\0', RGB_HEX_LENGTH + 1) ||
	    strlen(hex) < RGB_HEX_LENGTH) {
		*ok = false;
		return rgb;
	}

	unsigned long chans[3] = {0, 0, 0};
	char *hex_slice = "00";
	char *str_end;

	for (unsigned short i = 0; i < 3; i++) {
		memcpy(hex_slice, hex + i + i, 2);
		chans[i] = strtoul(hex_slice, &str_end, 16);
		if (*str_end != '\0') {
			*ok = false;
			return rgb;
		}
	}

	rgb.r = (double)chans[0] / 255.0;
	rgb.g = (double)chans[1] / 255.0;
	rgb.b = (double)chans[2] / 255.0;

	return rgb;
}
