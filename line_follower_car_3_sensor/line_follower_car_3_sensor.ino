#include <AFMotor.h>
int pwm = 140;      //speed that the motor follows
int vl = pwm - 30;

#define left A0
#define medium A1
#define right A2

bool lastDirectionRight = false; // Variable para recordar la última dirección del giro

AF_DCMotor motorL(2, MOTOR12_1KHZ);   
AF_DCMotor motorD(4, MOTOR34_1KHZ);

void setup() {
  pinMode(left, INPUT);
  pinMode(medium, INPUT);
  pinMode(right, INPUT);
}

void loop() {
  int valueLeft = digitalRead(left);
  int valueMedium = digitalRead(medium);
  int valueRight = digitalRead(right);

  // Línea detectada por el sensor medio o ambos laterales detectan blanco
  if ((valueLeft == 0 && valueMedium == 1 && valueRight == 0) || (valueLeft == 0 && valueRight == 0)) {
    motorL.run(FORWARD);
    motorL.setSpeed(pwm);
    motorD.run(FORWARD);
    motorD.setSpeed(pwm);
  }

  // Línea detectada por el sensor derecho, girar a la derecha
  if (valueLeft == 0 && valueMedium == 0 && valueRight == 1) {
    motorL.run(FORWARD);
    motorL.setSpeed(pwm);
    motorD.run(RELEASE);
    motorD.setSpeed(0);
    lastDirectionRight = true; // Recordar que el último giro fue a la derecha
  }

  // Línea detectada por el medio y derecho
  if (valueLeft == 0 && valueMedium == 1 && valueRight == 1) {
    motorL.run(FORWARD);
    motorL.setSpeed(pwm);
    motorD.run(FORWARD);
    motorD.setSpeed(vl);
    lastDirectionRight = true; // Recordar que el último giro fue a la derecha
  }

  // Línea detectada por el sensor izquierdo, girar a la izquierda
  if (valueLeft == 1 && valueMedium == 0 && valueRight == 0) {
    motorL.run(RELEASE);
    motorL.setSpeed(0);
    motorD.run(FORWARD);
    motorD.setSpeed(pwm);
    lastDirectionRight = false; // Recordar que el último giro fue a la izquierda
  }

  // Línea detectada por el medio e izquierdo
  if (valueLeft == 1 && valueMedium == 1 && valueRight == 0) {
    motorL.run(FORWARD);
    motorL.setSpeed(vl);
    motorD.run(FORWARD);
    motorD.setSpeed(pwm);
    lastDirectionRight = false; // Recordar que el último giro fue a la izquierda
  }

  // Todos los sensores detectan blanco (fuera de la línea)
  if (valueLeft == 0 && valueMedium == 0 && valueRight == 0) {
    if (lastDirectionRight) {
      // Si se salió por la izquierda, girar a la derecha
      motorL.run(FORWARD);
      motorL.setSpeed(pwm);
      motorD.run(RELEASE);
      motorD.setSpeed(0);
    } else {
      // Si se salió por la derecha, girar a la izquierda
      motorL.run(RELEASE);
      motorL.setSpeed(0);
      motorD.run(FORWARD);
      motorD.setSpeed(pwm);
    }
  }

  // Todos los sensores detectan negro (fin de la línea o parada)
  /* if (valueLeft == 1 && valueMedium == 1 && valueRight == 1) {
    motorL.run(RELEASE);
    motorD.run(RELEASE);
  } */
}
