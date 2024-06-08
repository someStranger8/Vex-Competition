
// standard libs
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

// vex api
#include "vex.h"

// define brain
using namespace vex;
brain Brain;

// define motor
motor fun = motor(PORT1, ratio6_1, false);

// main function
int main() {

  // print to screen
  Brain.Screen.print("One must imagine Sisyphus happy");

  // spin forever...
  // very slowly...
  fun.setVelocity(20, rpm);
  fun.spin(forward);

  // do we need this?
  return 0;
}
