#include "cielo.h"

#include <ctype.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////////////
// Constants //
///////////////

static const double RGB_TO_XYZ[3][3] = {
    {0.4124564, 0.3575761, 0.1804375},
    {0.2126729, 0.7151522, 0.0721750},
    {0.0193339, 0.1191920, 0.9503041}
};
static const double XYZ_TO_RGB[3][3] = {
    { 3.2404542, -1.5371385, -0.4985314},
    {-0.9692660,  1.8760108,  0.0415560},
    { 0.0556434, -0.2040259,  1.0572252}
};
static const double EPSILON = 216.0 / 24389.0;
static const double KAPPA = 24389.0 / 27.0;
static const double D65_ILLUMINANT[3] = {0.95047, 1.00000, 1.08883};
static const double PI = 3.14159265358979323846;
static const double D65_CHROMATICITY_COORDS[2] = {0.197839824821408,
                                                  0.468336302932410};

////////////////////////////
// Mathematical functions //
////////////////////////////

static void matrix_multiply_vector(const double M[3][3],
                                   const double v[3],
                                   double res[3])
{
  for (size_t i = 0; i < 3; i++) {
    res[i] = 0.0;
    for (size_t j = 0; j < 3; j++) {
      res[i] += M[i][j] * v[j];
    }
  }
}

static double degrees_to_radians(double degrees)
{
  return (PI / 180.0) * degrees;
}

static double radians_to_degrees(double radians)
{
  return (180.0 / PI) * radians;
}

//////////////////////
// Hex code <-> RGB //
//////////////////////

static bool rgb_validate_hex(const char* hex)
{
  if (!hex
      || *hex != '#'
      || !memchr(hex, '\0', RGB_HEX_LENGTH + 1)
      || strlen(hex) < RGB_HEX_LENGTH) {
    return false;
  }

  for (size_t i = 1; i < RGB_HEX_LENGTH; i++) {
    if (!isxdigit(hex[i])) {
      return false;
    }
  }

  return true;
}

Rgb rgb_from_hex(const char* hex, bool* ok)
{
  if (!rgb_validate_hex(hex)) {
    *ok = false;
    return (Rgb){.r = -1.0, .g = -1.0, .b = -1.0};
  }

  char hex_slice[3] = "00";
  double rgb_vec[3];

  for (size_t i = 0; i < 3; i++) {
    memcpy(hex_slice, hex + 2 * i + 1, 2);
    rgb_vec[i] = (double)strtoul(hex_slice, NULL, 16) / 255.0;
  }

  *ok = true;
  return (Rgb){.r = rgb_vec[0], .g = rgb_vec[1], .b = rgb_vec[2]};
}

void rgb_to_hex(const Rgb* rgb, char hex[RGB_HEX_LENGTH + 1])
{
  (void)snprintf(hex,
                 RGB_HEX_LENGTH + 1,
                 "#%02lx%02lx%02lx",
                 lround(rgb->r * 255.0),
                 lround(rgb->g * 255.0),
                 lround(rgb->b * 255.0));
}

/////////////////
// RGB <-> XYZ //
/////////////////

static double rgb_clamp(double x)
{
  return fmax(0.0, fmin(x, 1.0));
}

static double rgb_gamma(double x)
{
  return x > 0.0031308 ? 1.055 * pow(x, 1.0 / 2.4) - 0.055 : x * 12.92;
}

static double rgb_gamma_inverse(double x)
{
  return x > 0.04045 ? pow((x + 0.055) / 1.055, 2.4) : x / 12.92;
}

Xyz rgb_to_xyz(const Rgb* rgb)
{
  const double rgb_vec[3] = {rgb_gamma_inverse(rgb->r),
                             rgb_gamma_inverse(rgb->g),
                             rgb_gamma_inverse(rgb->b)};

  double xyz_vec[3];
  matrix_multiply_vector(RGB_TO_XYZ, rgb_vec, xyz_vec);

  return (Xyz){.x = xyz_vec[0], .y = xyz_vec[1], .z = xyz_vec[2]};
}

Rgb xyz_to_rgb(const Xyz* xyz)
{
  const double xyz_vec[3] = {xyz->x, xyz->y, xyz->z};

  double rgb_vec[3];
  matrix_multiply_vector(XYZ_TO_RGB, xyz_vec, rgb_vec);

  for (size_t i = 0; i < 3; i++) {
    rgb_vec[i] = rgb_clamp(rgb_gamma(rgb_vec[i]));
  }

  return (Rgb){.r = rgb_vec[0], .g = rgb_vec[1], .b = rgb_vec[2]};
}

/////////////////
// XYZ <-> Lab //
/////////////////

static double lab_transfer(double x)
{
  return x > EPSILON ? cbrt(x) : (KAPPA * x + 16.0) / 116.0;
}

static double lab_transfer_inverse(double x)
{
  return x > cbrt(EPSILON) ? x * x * x : (116.0 * x - 16.0) / KAPPA;
}

Lab xyz_to_lab(const Xyz* xyz)
{
  const double xyz_vec[3] = {xyz->x, xyz->y, xyz->z};

  double transfer_vals[3];
  for (size_t i = 0; i < 3; i++) {
    transfer_vals[i] = lab_transfer(xyz_vec[i] / D65_ILLUMINANT[i]);
  }

  return (Lab){
      .l = 116.0 * transfer_vals[1] - 16.0,
      .a = 500.0 * (transfer_vals[0] - transfer_vals[1]),
      .b = 200.0 * (transfer_vals[1] - transfer_vals[2]),
  };
}

Xyz lab_to_xyz(const Lab* lab)
{
  const double tmp = (lab->l + 16.0) / 116.0;
  const double inv_args[3] = {tmp + lab->a / 500.0, tmp, tmp - lab->b / 200.0};

  double xyz_vec[3];
  for (size_t i = 0; i < 3; i++) {
    xyz_vec[i] = D65_ILLUMINANT[i] * lab_transfer_inverse(inv_args[i]);
  }

  return (Xyz){.x = xyz_vec[0], .y = xyz_vec[1], .z = xyz_vec[2]};
}

///////////////////
// Lab <-> LCHab //
///////////////////

Lchab lab_to_lchab(const Lab* lab)
{
  const double h_degrees = radians_to_degrees(atan2(lab->b, lab->a));
  return (Lchab){.l = lab->l,
                 .c = hypot(lab->a, lab->b),
                 .h = h_degrees < 0.0 ? h_degrees + 360.0 : h_degrees};
}

Lab lchab_to_lab(const Lchab* lchab)
{
  const double h_radians = degrees_to_radians(lchab->h);
  return (Lab){.l = lchab->l,
               .a = lchab->c * cos(h_radians),
               .b = lchab->c * sin(h_radians)};
}

/////////////////
// XYZ <-> Luv //
/////////////////

Luv xyz_to_luv(const Xyz* xyz)
{
  const double l =
      xyz->y > EPSILON ? 116.0 * cbrt(xyz->y) - 16.0 : KAPPA * xyz->y;
  const double tmp = 13.0 * l;
  const double den = xyz->x + 15.0 * xyz->y + 3.0 * xyz->z;
  return (Luv){.l = l,
               .u = tmp * (4.0 * xyz->x / den - D65_CHROMATICITY_COORDS[0]),
               .v = tmp * (9.0 * xyz->y / den - D65_CHROMATICITY_COORDS[1])};
}
