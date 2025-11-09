// NOTE: This file is just for quick testing

#include "cielo.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "matrix.h"

int main(void)
{
  // rgb_validate_hex {{{
  const char red[] = "#EE4B2B";
  bool valid_red = rgb_validate_hex(red);
  printf("Hex code for red  is %s\n", valid_red ? "VALID" : "INVALID");

  const char lime[] = "32cd32";
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

  printf("Plum: Red   -> %.4f\n", plum.r);  // 0.8667
  printf("Plum: Green -> %.4f\n", plum.g);  // 0.6275
  printf("Plum: Blue  -> %.4f\n", plum.b);  // 0.8667

  // }}}

  // rgb_to_hex {{{
  const Rgb orange = {.r = 1.0, .g = 165.0 / 255.0, .b = 0.0};

  char orange_hex[8];
  rgb_to_hex(&orange, orange_hex);

  assert(strcmp(orange_hex, "#ffa500") == 0);
  printf("Orange Hex: %s\n", orange_hex);
  // }}}

  // matrix_multiply {{{
  const Matrix3 A = {
      {0.814, 0.223, 0.705},
      {0.612, 0.951, 0.137},
      {0.469, 0.388, 0.995}
  };
  const Matrix3 B = {
      {0.427, 0.913, 0.286},
      {0.731, 0.124, 0.859},
      {0.552, 0.678, 0.391}
  };

  Matrix3 C;
  matrix_multiply(C, A, B);  // C = A * B

  // Expected result:
  // C = {{0.899751, 1.24882, 0.700016},
  //      {1.03213, 0.769566, 1.04551},
  //      {1.03313, 1.15092, 0.856471}}

  printf("C[0][1] = %.5f\n", C[0][1]);
  printf("C[1][2] = %.5f\n", C[1][2]);
  printf("C[2][0] = %.5f\n", C[2][0]);
  // }}}

  // matrix_multiply_vector {{{
  const Matrix3 M = {
      {0.228, 0.888,  0.85},
      {0.259, 0.154, 0.183},
      {0.982, 0.075, 0.214}
  };
  const Vector3 v = {0.719, 0.048, 0.944};

  Vector3 u;
  matrix_multiply_vector(u, M, v);  // u = M * v

  // Expected result:
  // u = {1.008956, 0.366365, 0.911674}

  for (int i = 0; i < MATRIX_DIM; i++) {
    printf("u[%d] = %.6f\n", i, u[i]);
  }
  // }}}

  // rgb_to_xyz {{{
  const Rgb blue_rgb = {.r = 0.0, .g = 0.0, .b = 1.0};
  const Xyz blue_xyz = rgb_to_xyz(&blue_rgb);

  printf("Blue: X = %.6f\n", blue_xyz.x);  // 0.180438
  printf("Blue: Y = %.6f\n", blue_xyz.y);  // 0.072175
  printf("Blue: Z = %.6f\n", blue_xyz.z);  // 0.950304
  // }}}

  // xyz_to_rgb {{{
  // D65 illuminant -> should be white
  const Xyz d65_xyz = {.x = 0.95047, .y = 1.00000, .z = 1.08883};
  const Rgb d65_rgb = xyz_to_rgb(&d65_xyz);

  printf("D65: Red   = %.5f\n", d65_rgb.r);
  printf("D65: Green = %.5f\n", d65_rgb.g);
  printf("D65: Blue  = %.5f\n", d65_rgb.b);
  // }}}

  // xyz_to_lab {{{
  const Rgb gold_rgb = rgb_from_hex("#ffd700", &ok);
  assert(ok);

  const Xyz gold_xyz = rgb_to_xyz(&gold_rgb);
  const Lab gold_lab = xyz_to_lab(&gold_xyz);

  printf("Gold: L* = %.4f\n", gold_lab.l);  // 86.9306
  printf("Gold: a* = %.4f\n", gold_lab.a);  // -1.9237
  printf("Gold: b* = %.4f\n", gold_lab.b);  // 87.1320
  // }}}

  // lab_to_xyz {{{
  const Lab mint_lab = {.l = 66.1132, .a = -43.1697, .b = 12.4443};
  const Xyz mint_xyz = lab_to_xyz(&mint_lab);

  const Rgb mint_rgb = xyz_to_rgb(&mint_xyz);

  char mint_hex[8];
  rgb_to_hex(&mint_rgb, mint_hex);

  printf("Mint Hex: %s\n", mint_hex);  // #3eb489
  // }}}

  return 0;
}

// vim: foldmethod=marker
