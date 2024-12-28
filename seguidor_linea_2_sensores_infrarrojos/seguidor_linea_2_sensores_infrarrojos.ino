#include <AFMotor.h>
int speed = 170;      //Velocidad inicial
int vh = speed + 30; //Aceleracion
int vl = 0;  //Desaceleración de un motor

#define left A1
#define right A0

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
    motorL.setSpeed(speed);
    motorD.run(FORWARD);
    motorD.setSpeed(speed);
  }

  //line detected by right sensor
  if (valueLeft == 0 && valueRight == 1) {
    //turn rigth
    motorL.run(FORWARD);
    motorL.setSpeed(vh);
    motorD.run(RELEASE);
    motorD.setSpeed(vl);
  }
  //line detected by left sensor
  if (valueLeft == 1 && valueRight == 0) {
    //turn left
    motorL.run(RELEASE);
    motorL.setSpeed(vl);
    motorD.run(FORWARD);
    motorD.setSpeed(vh);
  }
  
  /* //line detected by none
  if (valueLeft == 1 && valueRight == 1) {
    motorL.run(RELEASE);
    motorD.run(RELEASE);
  } */
}
