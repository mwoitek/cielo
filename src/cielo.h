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

typedef struct {
  double l;
  double a;
  double b;
} Lab;

typedef struct {
  double l;
  double c;
  double h;
} Lchab;

Rgb rgb_from_hex(const char* hex, bool* ok);
void rgb_to_hex(const Rgb* rgb, char hex[RGB_HEX_LENGTH + 1]);

Xyz rgb_to_xyz(const Rgb* rgb);
Rgb xyz_to_rgb(const Xyz* xyz);

Lab xyz_to_lab(const Xyz* xyz);
Xyz lab_to_xyz(const Lab* lab);

Lchab lab_to_lchab(const Lab* lab);
Lab lchab_to_lab(const Lchab* lchab);

#endif
