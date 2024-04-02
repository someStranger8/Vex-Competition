
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>


#include "vex.h"

// macros
// NOTE: avoid magic numbers; use macros
#define FLYWHEEL_RPM 600 // make fly wheel 600 rpm instead of 500 (600 is the max rpm)
#define DRIVETRAIN_SPEED 100
#define WAIT_TIME 3 // how much delay seconds for automation

using namespace vex;

// Brain should be defined by default
brain Brain; 


// Robot configuration code.
controller Controller1 = controller(primary);
motor leftMotorA = motor(PORT1, ratio18_1, false);
motor leftMotorB = motor(PORT10, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT11, ratio18_1, true);
motor rightMotorB = motor(PORT20, ratio18_1, true);
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
    LeftDriveSmart.spin(reverse);
  }
  LeftDriveSmart.stop();
}

// left move forward
void l_mf() {
  while (Controller1.ButtonL1.pressing()) {
    RightDriveSmart.spin(reverse);
  }
  RightDriveSmart.stop();
}

// right move backward
void r_mb() {
  while (Controller1.ButtonR2.pressing()) {
    LeftDriveSmart.spin(forward);
  }
  LeftDriveSmart.stop();
}

// left move backward
void l_mb() {
  while (Controller1.ButtonL2.pressing()) {
    RightDriveSmart.spin(forward);
  } 
  RightDriveSmart.stop();
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

void random_colors() {

  // list of random colors
  char* colors[8] = {
    "\033[30m", // black
    "\033[31m", // red
    "\033[32m", // green
    "\033[33m", // yellow
    "\033[34m", // blue
    "\033[35m", // purple
    "\033[36m", // cyan
    "\033[37m"  // white
  };

  srand(time(NULL)); // init random

  printf(colors[rand() % sizeof(colors)]);
  Brain.Screen.print("Grumio est coquus");
}

int main(void) {

  // setup callbacks for competition
  competition Competition = competition();
  Competition.drivercontrol(driver);
  Competition.autonomous(capatalismAtItsPeak);

  random_colors();

  return 1; // remove this if code breaks
}
