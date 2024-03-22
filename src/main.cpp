
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

// macros
// NOTE: avoid magic numbers; use macros
#define FLYWHEEL_RPM 500
#define DRIVETRAIN_SPEED 150

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

// "when Controller1 ButtonR1 pressed" hat block
void onevent_Controller1ButtonR1_pressed_0() {
  while (Controller1.ButtonR1.pressing()) {
    LeftDriveSmart.spin(reverse);
  }
  LeftDriveSmart.stop();
}

// "when Controller1 ButtonL1 pressed" hat block
void onevent_Controller1ButtonL1_pressed_0() {
  while (Controller1.ButtonL1.pressing()) {
    RightDriveSmart.spin(reverse);
  }
  RightDriveSmart.stop();
}

// "when Controller1 ButtonR2 pressed" hat block
void onevent_Controller1ButtonR2_pressed_0() {
  while (Controller1.ButtonR2.pressing()) {
    LeftDriveSmart.spin(forward);
  }
  LeftDriveSmart.stop();
}

// "when Controller1 ButtonL2 pressed" hat block
void onevent_Controller1ButtonL2_pressed_0() {
  while (Controller1.ButtonL2.pressing()) {
    RightDriveSmart.spin(forward);
  } 
  RightDriveSmart.stop();
}

void onevent_ControllerButtonX_pressed_0() {
  flyWheel.spin(reverse);
  flyWheel.setVelocity(FLYWHEEL_RPM, rpm);
}

void onevent_ControllerButtonB_pressed_0() {
  flyWheel.stop();
}

// Driver Control
void setupDriver() {
  RightDriveSmart.setVelocity(DRIVETRAIN_SPEED, percent); 
  LeftDriveSmart.setVelocity(DRIVETRAIN_SPEED, percent);
}

// Controller
void handleMovement() {
  Controller1.ButtonL1.pressed(onevent_Controller1ButtonL1_pressed_0);
  Controller1.ButtonR1.pressed(onevent_Controller1ButtonR1_pressed_0);
  Controller1.ButtonL2.pressed(onevent_Controller1ButtonL2_pressed_0);
  Controller1.ButtonR2.pressed(onevent_Controller1ButtonR2_pressed_0);
}

void handleFlywheel() {
  Controller1.ButtonX.pressed(onevent_ControllerButtonX_pressed_0); // start
  Controller1.ButtonB.pressed(onevent_ControllerButtonB_pressed_0); // stop
}

void driver() {
  setupDriver(); 
  handleMovement();
  handleFlywheel();
}

// Automation
void capatalismAtItsPeak() {
  LeftDriveSmart.spin(reverse);
  RightDriveSmart.spin(reverse);
  wait(5, seconds);
  LeftDriveSmart.stop();
  RightDriveSmart.stop();
}


int main() {
  competition Competition = competition();
  Competition.drivercontrol(driver);


  // If the program breaks for some reason uncomment the following:
  // printf("\033[30m");
  Brain.Screen.print("Grumio est coquus");
}
