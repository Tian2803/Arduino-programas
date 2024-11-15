#include <AFMotor.h>
int pwm = 110;      //speed that the motor follows
int vl = pwm;  //acceleration
int vh = pwm - 30;  //deceleration

#define left A0
#define medium A1
#define right A2

AF_DCMotor motorL(2, MOTOR12_1KHZ);    //1
AF_DCMotor motorD(4, MOTOR34_1KHZ);  //3

void setup() {
  pinMode(left, INPUT);
  pinMode(medium, INPUT);
  pinMode(right, INPUT);
}

void loop() {
  int valueLeft = digitalRead(left);
  int valueMedium = digitalRead(medium);
  int valueRight = digitalRead(right);

  if (valueMedium == 1 || (valueLeft == 0 && valueRight == 0)) {
    motorL.run(FORWARD);
    motorL.setSpeed(pwm);
    motorD.run(FORWARD);
    motorD.setSpeed(pwm);
  }

  //line detected by right sensor
  if (valueLeft == 0 && valueMedium == 0 && valueRight == 1) {
    //turn rigth
    motorL.run(FORWARD);
    motorL.setSpeed(vl);
    motorD.run(BACKWARD);
    motorD.setSpeed(vh);
  }
  //line detected by left sensor
  if (valueLeft == 1 && valueMedium == 0 && valueRight == 0) {
    //turn left
    motorL.run(BACKWARD);
    motorL.setSpeed(vh);
    motorD.run(FORWARD);
    motorD.setSpeed(vl);
  }
}