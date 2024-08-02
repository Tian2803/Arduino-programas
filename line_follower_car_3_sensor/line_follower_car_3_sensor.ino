#include <AFMotor.h>
int pwm = 105;      //speed that the motor follows
int vl = pwm + 1;  //acceleration
int vh = pwm - 40;  //deceleration

#define left A0
#define medium A1
#define right A2

AF_DCMotor motorL(1, MOTOR12_1KHZ);    //1
AF_DCMotor motorD(3, MOTOR12_1KHZ);  //3

void setup() {
  pinMode(left, INPUT);
  pinMode(medium, INPUT);
  pinMode(right, INPUT);
}

void loop() {
  int valueLeft = digitalRead(left);
  int valueMedium = digitalRead(medium);
  int valueRight = digitalRead(right);

  if ((valueLeft == 0 && valueMedium == 0 && valueRight == 0) && (valueLeft == 1 && valueMedium == 0 && valueRight == 1)) {
    motorL.run(BACKWARD);
    motorL.setSpeed(pwm);
    motorD.run(BACKWARD);
    motorD.setSpeed(pwm);
  }

  //line detected by right sensor
  if (valueLeft == 1 && valueMedium == 1 && valueRight == 0) {
    //turn rigth
    motorL.run(BACKWARD);
    motorL.setSpeed(vl);
    motorD.run(FORWARD);
    motorD.setSpeed(vh);
  }
  //line detected by left sensor
  if (valueLeft == 0 && valueMedium == 1 && valueRight == 1) {
    //turn left
    motorL.run(FORWARD);
    motorL.setSpeed(vh);
    motorD.run(BACKWARD);
    motorD.setSpeed(vl);
  }
  //line detected by none
  if (valueLeft == 1 && valueMedium == 1 && valueRight == 1) {
    motorL.run(BACKWARD);
    motorL.setSpeed(pwm);
    motorD.run(BACKWARD);
    motorD.setSpeed(pwm);
  }
}