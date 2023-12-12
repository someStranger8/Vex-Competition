
#include "config.h"

void r_drive_forward() {
  RightDriveSmart.spinFor(forward, 360, degrees);
}

void r_drive_backward() {
  RightDriveSmart.spinFor(reverse, 360, degrees);
}
void l_drive_forward() {
  LeftDriveSmart.spinFor(forward, 360, degrees);
}

void l_drive_backward() {
  LeftDriveSmart.spinFor(reverse, 360, degrees);
}

void controller_handler() {
  Con.ButtonL1.pressed(l_drive_forward);
  Con.ButtonL2.pressed(l_drive_backward);

  Con.ButtonR1.pressed(r_drive_forward);
  Con.ButtonR2.pressed(r_drive_backward);
}


int main() {
  controller_handler(); // handle controller input
}
