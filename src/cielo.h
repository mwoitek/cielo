#ifndef _CIELO_H_
#define _CIELO_H_

#include <stdbool.h>

// TODO: remove
float cube(float x);

typedef struct {
	double r;
	double g;
	double b;
} Rgb;

typedef struct {
	double x;
	double y;
	double z;
} Xyz;

bool rgb_validate_hex(const char *hex);
Rgb rgb_from_hex(const char *hex, bool *ok);

double rgb_gamma_inverse(double x);
double rgb_gamma(double x);
double rgb_clamp(double x);

Xyz rgb_to_xyz(const Rgb *rgb);
Rgb xyz_to_rgb(const Xyz *xyz);

#endif // _CIELO_H_
