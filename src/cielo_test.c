#include "cielo.h"

#include <stdio.h>

int main(void)
{
  //////////////////
  // rgb_from_hex //
  //////////////////
  bool ok = false;
  const Rgb plum = rgb_from_hex("#DDA0DD", &ok);
  if (ok) {
    printf("Plum: Red   = %.6f\n", plum.r);  // 0.866667
    printf("Plum: Green = %.6f\n", plum.g);  // 0.627451
    printf("Plum: Blue  = %.6f\n", plum.b);  // 0.866667
  } else {
    printf("Failed to convert hex code to RGB!!!!!\n");
  }

  printf("\n");

  ////////////////
  // rgb_to_hex //
  ////////////////
  const Rgb orange = {.r = 1.0, .g = 165.0 / 255.0, .b = 0.0};
  char orange_hex[8];
  rgb_to_hex(&orange, orange_hex);
  printf("Orange: Hex = %s\n", orange_hex);  // #ffa500

  printf("\n");

  ////////////////
  // rgb_to_xyz //
  ////////////////
  const Rgb blue_rgb = {.r = 0.0, .g = 0.0, .b = 1.0};
  const Xyz blue_xyz = rgb_to_xyz(&blue_rgb);
  printf("Blue: X = %.6f\n", blue_xyz.x);  // 0.180437
  printf("Blue: Y = %.6f\n", blue_xyz.y);  // 0.072175
  printf("Blue: Z = %.6f\n", blue_xyz.z);  // 0.950304

  printf("\n");

  ////////////////
  // xyz_to_rgb //
  ////////////////
  const Xyz chestnut_xyz = {.x = 0.151665, .y = 0.109047, .z = 0.046736};
  const Rgb chestnut_rgb = xyz_to_rgb(&chestnut_xyz);
  printf("Chestnut: Red   = %.6f\n", chestnut_rgb.r);  // 0.584314
  printf("Chestnut: Green = %.6f\n", chestnut_rgb.g);  // 0.270589
  printf("Chestnut: Blue  = %.6f\n", chestnut_rgb.b);  // 0.207843

  printf("\n");

  ////////////////
  // xyz_to_lab //
  ////////////////
  const Xyz gold_xyz = {.x = 0.655445, .y = 0.698649, .z = 0.100330};
  const Lab gold_lab = xyz_to_lab(&gold_xyz);
  printf("Gold: L* = %.4f\n", gold_lab.l);  // 86.9306
  printf("Gold: a* = %.4f\n", gold_lab.a);  // -1.9237
  printf("Gold: b* = %.4f\n", gold_lab.b);  // 87.1320

  printf("\n");

  ////////////////
  // lab_to_xyz //
  ////////////////
  const Lab mint_lab = {.l = 66.1132, .a = -43.1697, .b = 12.4443};
  const Xyz mint_xyz = lab_to_xyz(&mint_lab);
  printf("Mint: X = %.6f\n", mint_xyz.x);  // 0.228208
  printf("Mint: Y = %.6f\n", mint_xyz.y);  // 0.354703
  printf("Mint: Z = %.6f\n", mint_xyz.z);  // 0.293058

  return 0;
}
