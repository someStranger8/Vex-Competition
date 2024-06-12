
// standard libs
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

// vex api and macros
#include "vex.h"
#include "macros.h"

using namespace vex;

// brain should be defined by default
brain Brain; 


// robot configuration code
// this is ugly and hurts my eyes :(
controller Controller1 = controller(primary);
motor leftMotorA = motor(PORT11, ratio18_1, true);
motor leftMotorB = motor(PORT20, ratio18_1, true);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT1, ratio18_1, true);
motor rightMotorB = motor(PORT10, ratio18_1, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
motor flyWheel = motor(PORT2, ratio18_1, true);
bool flyWheel_is_spinning = false;

// define variable for remote controller enable/disable
// why is this required?
// vex api docs make no sense
//bool RemoteControlCodeEnabled = true; //swapfile

void kill(void) {
  abort();
}

/*
 * DO NOT TOUCH THE MOVEMENT FUNCTIONS BELLOW
 * THEY WILL BRAKE
 *
 * ^ say thank you to nick for that :)
 *
 * can you put the following functions into a class please?
*/

// right move forward
void r_mf(void) {
  while (Controller1.ButtonR1.pressing()) {
    RightDriveSmart.spin(forward);
  }
  RightDriveSmart.stop();
}

// left move forward
void l_mf(void) {
  while (Controller1.ButtonL1.pressing()) {
    LeftDriveSmart.spin(forward);
  }
  LeftDriveSmart.stop();
}

// right move backward
void r_mb(void) {
  while (Controller1.ButtonR2.pressing()) {
    RightDriveSmart.spin(reverse);
  }
  RightDriveSmart.stop();
}

// left move backward
void l_mb(void) {
  while (Controller1.ButtonL2.pressing()) {
    LeftDriveSmart.spin(reverse);
  } 
  LeftDriveSmart.stop();
}

// flywheel start
void flywheel_toggle(void) {
  switch (flyWheel_is_spinning) {
    case true:
      flyWheel.stop();
      flyWheel_is_spinning = false;

    case false:
      flyWheel.spin(forward);
      flyWheel_is_spinning = true;

    default:
      kill();
  }
}


// driver control callback
void driver(void) {

  // setup drivetrain and flywheel
  RightDriveSmart.setVelocity(DRIVETRAIN_SPEED, rpm);
  LeftDriveSmart.setVelocity(DRIVETRAIN_SPEED, rpm);
  flyWheel.setVelocity(FLYWHEEL_RPM, rpm);
  
  // setup movement controls
  Controller1.ButtonL1.pressed(l_mf);
  Controller1.ButtonR1.pressed(r_mf);
  Controller1.ButtonL2.pressed(l_mb);
  Controller1.ButtonR2.pressed(r_mb);

  // flywheel controls
  Controller1.ButtonX.pressed(flywheel_toggle);

  // kill button
  Controller1.ButtonA.pressed(kill);
}

// automation
// hehe funny name
// NOTE: We should work on this function
void capatalism_at_its_peak(void) {
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  wait(WAIT_TIME, seconds);
  LeftDriveSmart.stop();
  RightDriveSmart.stop();
}

// main function
// // the "void" isnt standard
void main(void) {

  // setup callbacks for competition
  competition Competition = competition();
  Competition.drivercontrol(driver);
  Competition.autonomous(capatalism_at_its_peak);
}

