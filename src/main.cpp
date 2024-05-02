
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>


#include "vex.h"
#include "macros.h"

using namespace vex;

// Brain should be defined by default
brain Brain; 


// Robot configuration code.
controller Controller1 = controller(primary);
motor leftMotorA = motor(PORT11, ratio18_1, false);
motor leftMotorB = motor(PORT20, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT1, ratio18_1, false);
motor rightMotorB = motor(PORT10, ratio18_1, false);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
motor flyWheel = motor(PORT2, ratio18_1, true);


// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;


/*
  DO NOT TOUCH THE FOLLOWING MOVEMENT FUNCTIONS
  THEY WILL PROBABLY BREAK
*/

// right move forward
void r_mf() {
  while (Controller1.ButtonR1.pressing()) {
    RightDriveSmart.spin(reverse);
  }
  RightDriveSmart.stop();
}

// left move forward
void l_mf() {
  while (Controller1.ButtonL1.pressing()) {
    LeftDriveSmart.spin(reverse);
  }
  LeftDriveSmart.stop();
}

// right move backward
void r_mb() {
  while (Controller1.ButtonR2.pressing()) {
    RightDriveSmart.spin(forward);
  }
  RightDriveSmart.stop();
}

// left move backward
void l_mb() {
  while (Controller1.ButtonL2.pressing()) {
    LeftDriveSmart.spin(forward);
  } 
  LeftDriveSmart.stop();
}

void flywheel_spin() {
  flyWheel.setVelocity(FLYWHEEL_RPM, rpm); // set velocity before starting
  flyWheel.spin(reverse);
}

void flywheel_stop() {
  flyWheel.stop();
}

// driver control setup
void setupDriver() {
  RightDriveSmart.setVelocity(DRIVETRAIN_SPEED, percent); 
  LeftDriveSmart.setVelocity(DRIVETRAIN_SPEED, percent);
}

// map input to movement call back funcs
void handleMovement() {
  Controller1.ButtonL1.pressed(l_mf);
  Controller1.ButtonR1.pressed(r_mf);
  Controller1.ButtonL2.pressed(l_mb);
  Controller1.ButtonR2.pressed(r_mb);
}

// map input to flywheel call back functions
void handleFlywheel() {
  Controller1.ButtonX.pressed(flywheel_spin); // start
  Controller1.ButtonB.pressed(flywheel_stop); // stop
}

// driver control callback
void driver() {

  // why are these seperate?

  setupDriver(); 
  handleMovement();
  handleFlywheel();
}

// Automation
void capatalismAtItsPeak() {

  LeftDriveSmart.spin(reverse);
  RightDriveSmart.spin(reverse);
  wait(WAIT_TIME, seconds);
  LeftDriveSmart.stop();
  RightDriveSmart.stop();
}

// display image from sd card
void display_image(string name) {
  /*
    Can use this to draw an image to the screen from sd card:
    Brain.Screen.drawImageFromFile(name, x, y);

    But it must be a .png or a .bmp file and
    cannot be bigger than 480x240px
  */

  //Brain.Screen.drawImageFromFile(name, 0, 0);
}

int main(void) {

  // setup callbacks for competition
  competition Competition = competition();
  Competition.drivercontrol(driver);
  Competition.autonomous(capatalismAtItsPeak);

  //display_image("image.png");

  return 1; // remove this if code breaks
}
