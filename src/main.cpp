

// file inclusion
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

// leave "" separate from <>
#include "vex.h"


// macros
// NOTE: avoid magic numbers; use macros
#define FLYWHEEL_SPEED 500
#define DRIVETRAIN_SPEED 100

// may remove this later idk
using namespace vex;

// Brain should be defined by default
brain Brain; 

// Robot configuration code.
controller Controller = controller(primary);

// if bug uncomment
//bool RemoteControlCodeEnabled = true;


class driveTrain() {

  // Private stuff
  private:
    // declare motors
    motor lA = motor(PORT1, ratio18_1, false);
    motor lB = motor(PORT10, ratio18_1, false);
    motor_group left = motor_group(lA, lB);
    motor rA = motor(PORT11, ratio18_1, true);
    motor rB = motor(PORT20, ratio18_1, true);
    motor_group right = motor_group(rA, rB);

    // set velocity
    right.setVelocity(DRIVETRAIN_SPEED, rpm); 
    left.setVelocity(DRIVETRAIN_SPEED, rpm);

  // public stuff
  public:

    /*

      Nick messed up motors so there reversed and inverted
      Who let this happen?
    
    */
  
    void right_forward() {
      while (Controller.ButtonR1.pressing()) {
        left.spin(reverse);
      }
      left.stop();
    }
    
    void left_forward() {
      while (Controller.ButtonL1.pressing()) {
        right.spin(reverse);
      }
      right.stop();
    }
    
    void right_backward() {
      while (Controller.ButtonR2.pressing()) {
        left.spin(forward);
      }
      left.stop();
    }
    
    void left_backward() {
      while (Controller.ButtonL2.pressing()) {
        right.spin(forward);
      } 
      right.stop();
    }
}


class flyWheel {

  private:
    // declare motors
    motor fly_wheel = motor(PORT2, ratio18_1, true);
    fly_wheel.setVelocity(FLYWHEEL_SPEED, rpm);

  public:

    /*

      Nick messed up motors so there reversed and inverted
      Who let this happen?
    
    */

    void start() {
      fly_wheel.spin(reverse);
    }
    
    void stop() {
      fly_wheel.stop();
    }

}

// Controller
void handle_movement() {

  driveTrain DTClass = driveTrain();
  
  Controller1.ButtonL1.pressed(DTClass.left_forward);
  Controller1.ButtonR1.pressed(DTClass.right_forward);
  Controller1.ButtonL2.pressed(DTClass.left_backward);
  Controller1.ButtonR2.pressed(oDTClass.right_backward);
  
}

void handle_fly_wheel() {

  flyWheel flywheel = flyWheel();
  
  Controller1.ButtonX.pressed(flywheel.start); // start
  Controller1.ButtonB.pressed(flywheel.stop); // stop
  
}

void driver() {
  // why?
  
  handle_movement();
  handle_fly_wheel();

}


// Automation
void capatalism_at_its_peak() {  // funny name lol
  
  // fix this later

  return;
  
}


int main() {

  // stuff for competition
  competition Competition = competition();
  Competition.drivercontrol(driver);
  Competition.autonomous(capatalism_at_its_peak);

  // If the program breaks for some reason uncomment the following:
  // printf("\033[30m");

  // print funny thing
  Brain.Screen.print("Grumio est coquus");
  
}
