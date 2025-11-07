#include "cielo.h"
#include "matrix.h"
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

const Matrix3 RGB_TO_XYZ = {{0.4124564, 0.3575761, 0.1804375},
			    {0.2126729, 0.7151522, 0.0721750},
			    {0.0193339, 0.1191920, 0.9503041}};
const Matrix3 XYZ_TO_RGB = {{3.2404542, -1.5371385, -0.4985314},
			    {-0.9692660, 1.8760108, 0.0415560},
			    {0.0556434, -0.2040259, 1.0572252}};

// TODO: remove
float cube(float x)
{
	return powf(x, 3.0F);
}

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
	Rgb rgb = {.r = -1.0, .g = -1.0, .b = -1.0};

	if (!rgb_validate_hex(hex)) {
		*ok = false;
		return rgb;
	}

	char hex_slice[3] = "00";
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

double rgb_gamma_inverse(double x)
{
	return x > 0.04045 ? pow((x + 0.055) / 1.055, 2.4) : x / 12.92;
}

double rgb_gamma(double x)
{
	return x > 0.0031308 ? 1.055 * pow(x, 1.0 / 2.4) - 0.055 : x * 12.92;
}

double rgb_clamp(double x)
{
	return fmax(0.0, fmin(x, 1.0));
}

Xyz rgb_to_xyz(const Rgb *rgb)
{
	const Vector3 rgb_vec = {rgb_gamma_inverse(rgb->r),
				 rgb_gamma_inverse(rgb->g),
				 rgb_gamma_inverse(rgb->b)};

	Vector3 xyz_vec;
	matrix_multiply_vector(xyz_vec, RGB_TO_XYZ, rgb_vec);

	return (Xyz){.x = xyz_vec[0], .y = xyz_vec[1], .z = xyz_vec[2]};
}

Rgb xyz_to_rgb(const Xyz *xyz)
{
	const Vector3 xyz_vec = {xyz->x, xyz->y, xyz->z};

	Vector3 rgb_vec;
	matrix_multiply_vector(rgb_vec, XYZ_TO_RGB, xyz_vec);

	for (size_t i = 0; i < MATRIX_DIM; i++) {
		rgb_vec[i] = rgb_clamp(rgb_gamma(rgb_vec[i]));
	}

	return (Rgb){.r = rgb_vec[0], .g = rgb_vec[1], .b = rgb_vec[2]};
}
