#include <AFMotor.h>
int pwm = 120;      //speed that the motor follows
int vl = pwm + 20;  //acceleration
int vh = pwm - 50;  //deceleration

#define left A0
#define medLeft A1
#define medium A2
#define medRight A3
#define right A4

AF_DCMotor motorL(3, MOTOR12_1KHZ);
AF_DCMotor motorD(2, MOTOR12_1KHZ);

void setup() {
  pinMode(left, INPUT);
  pinMode(medLeft, INPUT);
  pinMode(medium, INPUT);
  pinMode(medRight, INPUT);
  pinMode(right, INPUT);
}

void loop() {
  int valueLeft = digitalRead(left);
  int valueMLeft = digitalRead(medLeft);
  int valueMedium = digitalRead(medium);
  int valueMRight = digitalRead(medRight);
  int valueRight = digitalRead(right);

  //line detected by sensor medium
  if (valueMedium == 0) {
    motorL.run(BACKWARD);
    motorL.setSpeed(pwm);
    motorD.run(BACKWARD);
    motorD.setSpeed(pwm);
  }

  //line detected by sensor mediumLeft, medium, mediumRight
  if (valueMLeft == 0 && valueMedium == 0 && valueMRight == 0) {
    motorL.run(BACKWARD);
    motorL.setSpeed(pwm);
    motorD.run(BACKWARD);
    motorD.setSpeed(pwm);
  }

  //line detected by left sensor
  if (valueLeft == 0) {
    motorL.run(BACKWARD);
    motorL.setSpeed(vh);
    motorD.run(BACKWARD);
    motorD.setSpeed(vl);
  }

  //line detected by leftMedium sensor
  if (valueMLeft == 0) {
    //turn left
    motorL.run(BACKWARD);
    motorL.setSpeed(pwm);
    motorD.run(BACKWARD);
    motorD.setSpeed(vl);
  }

  //line detected by mediumRight sensor
  if (valueMRight == 0) {
    //turn rigth
    motorL.run(BACKWARD);
    motorL.setSpeed(pwm);
    motorD.run(BACKWARD);
    motorD.setSpeed(vh);
  }

  //line detected by Right sensor
  if (valueRight == 0) {
    //turn rigth
    motorL.run(BACKWARD);
    motorL.setSpeed(vl);
    motorD.run(BACKWARD);
    motorD.setSpeed(vh);
  }

  if (valueLeft == 0 && valueMLeft == 0) {
    //turn left
    motorL.run(BACKWARD);
    motorL.setSpeed(vh);
    motorD.run(BACKWARD);
    motorD.setSpeed(vl);
  }

  if (valueLeft == 0 && valueMLeft == 0 && valueMedium == 0) {
    //turn rigth
    motorL.run(BACKWARD);
    motorL.setSpeed(vh);
    motorD.run(BACKWARD);
    motorD.setSpeed(pwm);
  }

  if (valueRight == 0 && valueMRight == 0) {
    //turn rigth
    motorL.run(BACKWARD);
    motorL.setSpeed(vl);
    motorD.run(BACKWARD);
    motorD.setSpeed(vh);
  }

  if (valueRight == 0 && valueMRight == 0 && valueMedium == 0) {
    //turn rigth
    motorL.run(BACKWARD);
    motorL.setSpeed(pwm);
    motorD.run(BACKWARD);
    motorD.setSpeed(vh);
  }

  //line detected by none
  if (valueLeft == 1 && valueMLeft == 1 && valueMedium == 1 && valueMRight == 1 && valueRight == 1) {
    motorL.run(BACKWARD);
    motorL.setSpeed(pwm);
    motorD.run(BACKWARD);
    motorD.setSpeed(pwm);
  }
}