
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


// define variable for remote controller enable/disable
// why is this required?
// vex api docs make no sense
//bool RemoteControlCodeEnabled = true; //swapfile


/*
 * DO NOT TOUCH THE MOVEMENT FUNCTIONS BELLOW
 * THEY WILL BRAKE
 *
 * ^ say thank you to nick for that :)
 *
 * can you put the following functions into a class please?
*/

// right move forward
void r_mf() {
  while (Controller1.ButtonR1.pressing()) {
    RightDriveSmart.spin(forward);
  }
  RightDriveSmart.stop();
}

// left move forward
void l_mf() {
  while (Controller1.ButtonL1.pressing()) {
    LeftDriveSmart.spin(forward);
  }
  LeftDriveSmart.stop();
}

// right move backward
void r_mb() {
  while (Controller1.ButtonR2.pressing()) {
    RightDriveSmart.spin(reverse);
  }
  RightDriveSmart.stop();
}

// left move backward
void l_mb() {
  while (Controller1.ButtonL2.pressing()) {
    LeftDriveSmart.spin(reverse);
  } 
  LeftDriveSmart.stop();
}

// flywheel start
void flywheel_spin() {
  flyWheel.setVelocity(FLYWHEEL_RPM, rpm); // set velocity before starting
  flyWheel.spin(forward);
}

// flywheel start
void flywheel_stop() {
  flyWheel.stop();
}

// driver control setup
void setupDriver() {
  RightDriveSmart.setVelocity(DRIVETRAIN_SPEED, rpm); 
  LeftDriveSmart.setVelocity(DRIVETRAIN_SPEED, rpm);
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
  // this code is redundant

  setupDriver(); 
  handleMovement();
  handleFlywheel();
}

// automation
// hehe funny name
// NOTE: We should work on this function
void capatalism_at_its_peak() {
  LeftDriveSmart.spin(reverse);
  RightDriveSmart.spin(reverse);
  wait(WAIT_TIME, seconds);
  LeftDriveSmart.stop();
  RightDriveSmart.stop();
}


// main function
int main(void) {

  // setup callbacks for competition
  competition Competition = competition();
  Competition.drivercontrol(driver);
  Competition.autonomous(capatalism_at_its_peak);

  // the code should never hit this return function
  return 1; // remove this if code breaks
}

