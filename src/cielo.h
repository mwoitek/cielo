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

bool rgb_validate_hex(const char *hex);
Rgb rgb_from_hex(const char *hex, bool *ok);

double rgb_gamma(double x);
double rgb_gamma_inv(double x);

#endif // _CIELO_H_
