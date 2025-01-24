/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Srihaas                                                   */
/*    Created:      I dunno???                                                */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include <algorithm>
using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
///////////Controller Stuff////////////////
void BX(){
  pn.set(false);
}
void BB(){
  pn.set(true);
}

motor leftBack = motor (PORT13);
motor leftFront = motor (PORT10);
motor leftTop = motor (PORT8, false);
motor_group leftmtrs = motor_group(leftBack, leftFront);
motor RightBack = motor (PORT18);
motor RightFront = motor (PORT17);
motor RightTop = motor (PORT16, false);
motor_group rightmtrs = motor_group(RightBack, RightFront);
motor intake = motor (PORT19);

motor hook = motor (PORT9);
void R1(){
  hook.spin(forward);
}
void R2(){
  hook.spin(reverse);
}
void L1(){
  intake.spin(forward);
}
void L2(){
  intake.spin(reverse);
}
void stopintake(){
  intake.stop();
}
void stophook(){
  hook.stop();
}

// PID constants
double kP = 1;
double kI = 1;
double kD = 0.5;

double clamp(double value, double minValue, double maxValue) {
    if (value > maxValue) return maxValue;
    if (value < minValue) return minValue;
    return value;
}


void driveAndTurnPID(double distance, double turnDegrees, int maxSpeed) {
    // Constants
    double wheelDiameter = 3.25; // inches
    double wheelCircumference = 3.14 * wheelDiameter; 
    double wheelbase = 12.0; // Distance between left/right wheels (inches)
    double degreesPerInch = 360 / wheelCircumference; 

    // Targets
    double driveTarget = distance * degreesPerInch; 
    double turnTarget = (turnDegrees / 360.0) * (3.14 * wheelbase / wheelCircumference) * 360; 

    // PID Variables
    double kP = 0.6, kI = 0.0, kD = 0.2; // Tune as needed
    double leftError = driveTarget, rightError = driveTarget;
    double leftLastError = 0, rightLastError = 0;
    double leftIntegral = 0, rightIntegral = 0;

    while (fabs(leftError) > 5 || fabs(rightError) > 5) { // End condition
        // Current motor positions
        double leftPosition = leftmtrs.position(degrees);
        double rightPosition = rightmtrs.position(degrees);

        // Update errors
        leftError = driveTarget + turnTarget - leftPosition;
        rightError = driveTarget - turnTarget - rightPosition;

        // PID Calculations
        leftIntegral += leftError;
        rightIntegral += rightError;
        double leftDerivative = leftError - leftLastError;
        double rightDerivative = rightError - rightLastError;

        // Motor power
        double leftPower = kP * leftError + kI * leftIntegral + kD * leftDerivative;
        double rightPower = kP * rightError + kI * rightIntegral + kD * rightDerivative;

        // Clamp power
        leftPower = clamp(leftPower, -maxSpeed, maxSpeed);
        rightPower = clamp(rightPower, -maxSpeed, maxSpeed);



        // Set motors
        leftmtrs.spin(forward, leftPower, percent);
        rightmtrs.spin(forward, rightPower, percent);

        // Update errors
        leftLastError = leftError;
        rightLastError = rightError;

        wait(20, msec); // Small delay for stability
    }

    // Stop motors
    leftmtrs.stop(brake);
    rightmtrs.stop(brake);
}


///////////////////////////////////////////
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
 Drivetrain.setDriveVelocity(80,percent);
  Drivetrain.setTurnVelocity(100,percent);
  hook.setVelocity(80, percent);
  hook.setMaxTorque(100,percent);
  intake.setVelocity(100, percent);
  pn.set(false);
  Controller1.ButtonX.pressed(BX);
  Controller1.ButtonB.pressed(BB);
    Controller1.ButtonR1.pressed(R1);
  Controller1.ButtonR2.pressed(R2);
    Controller1.ButtonL1.pressed(L1);
  Controller1.ButtonL2.pressed(L2);
 Controller1.ButtonL1.released(stophook);
 Controller1.ButtonL2.released(stophook);
 Controller1.ButtonR1.released(stopintake);
 Controller1.ButtonR2.released(stopintake);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
    Drivetrain.setDriveVelocity(20, percent);
  Drivetrain.setTurnVelocity(50,percent);
  hook.setVelocity(55,percent);
  pn.set(true);
 driveAndTurnPID(24, 0, 50);  // Drive forward 36 inches

  /*intake.spin(reverse);
  //Going for MoGO
  Drivetrain.drive(reverse);
  wait(1.1,seconds);
  pn.set(false);
  //Clamps
  wait(0.30,seconds);
  Drivetrain.stop();
  //Stops with the MoGo
  //Turns
  Drivetrain.turn(right);
  wait(0.65,seconds);
  Drivetrain.stop();
  //Goes for 1st donut
  hook.spin(forward);
  intake.spin(reverse);
  Drivetrain.drive(forward);
  wait(1.5,seconds);
  Drivetrain.stop();
  //Goes to ladder
  Drivetrain.turn(right);
  wait(1.6,seconds);
  Drivetrain.stop();
  
  Drivetrain.driveFor(forward,55,inches);
  hook.stop();
  intake.stop();
  //Done
*\
  //////////////////////////////////////////////*/
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
 Drivetrain.setDriveVelocity(60,percent);
Drivetrain.setTurnVelocity(100,percent);
hook.setVelocity(50,percent);
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
