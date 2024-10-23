#include <AFMotor.h>
int pwm = 120;      //speed that the motor follows
int vl = pwm + 10;  //acceleration
int vh = pwm - 30;  //deceleration

#define left A3
#define right A1

AF_DCMotor motorL(2, MOTOR12_1KHZ);
AF_DCMotor motorD(4, MOTOR34_1KHZ);

void setup() {
  pinMode(left, INPUT);
  pinMode(right, INPUT);
}

void loop() {
  int valueLeft = digitalRead(left);
  int valueRight = digitalRead(right);

  if (valueLeft == 0 && valueRight == 0) {
    motorL.run(FORWARD);
    motorL.setSpeed(pwm);
    motorD.run(FORWARD);
    motorD.setSpeed(pwm);
  }

  //line detected by right sensor
  if (valueLeft == 0 && valueRight == 1) {
    //turn rigth
    motorL.run(BACKWARD);
    motorL.setSpeed(vh);
    motorD.run(FORWARD);
    motorD.setSpeed(vl);
  }
  //line detected by left sensor
  if (valueLeft == 1 && valueRight == 0) {
    //turn left
    motorL.run(FORWARD);
    motorL.setSpeed(vl);
    motorD.run(BACKWARD);
    motorD.setSpeed(vh);
  }
  //line detected by none
  if (valueLeft == 1 && valueRight == 1) {
    motorL.run(RELEASE);
    motorD.run(RELEASE);
  }
}
