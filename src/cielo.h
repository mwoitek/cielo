#ifndef __CIELO_H__
#define __CIELO_H__

#include <stdbool.h>

#define RGB_HEX_LENGTH 7

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

bool rgb_validate_hex(const char* hex);
Rgb rgb_from_hex(const char* hex, bool* ok);
void rgb_to_hex(const Rgb* rgb, char out[RGB_HEX_LENGTH + 1]);

double rgb_gamma_inverse(double x);
double rgb_gamma(double x);
double rgb_clamp(double x);

Xyz rgb_to_xyz(const Rgb* rgb);
Rgb xyz_to_rgb(const Xyz* xyz);

#endif
