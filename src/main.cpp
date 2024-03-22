
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "vex.h"

using namespace vex;
brain Brain;

motor fun = motor(PORT1, ratio6_1, false);

int main() {
  printf("%s\n", "music");
  Brain.Screen.print("One must imagine Sisyphus happy");

  fun.setVelocity(15, rpm);
  fun.spin(forward);

  return 0;
}
