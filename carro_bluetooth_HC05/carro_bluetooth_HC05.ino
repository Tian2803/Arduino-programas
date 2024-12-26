#include <AFMotor.h>
//Inicializacion, pin de motores
AF_DCMotor motorI1(1, MOTOR12_1KHZ);
AF_DCMotor motorI2(4, MOTOR34_1KHZ);
AF_DCMotor motorD1(2, MOTOR12_1KHZ);
AF_DCMotor motorD2(3, MOTOR34_1KHZ);

// int speed = 255;

char command;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();
    stop();  //initialize with motors stoped
    switch (command) {
      case 'F':
        forward();
        break;
      case 'B':
        backward();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 'G':
        forwardLeft();
        break;
      case 'I':
        forwardRight()
          : break;
      case 'H':
        backwardLeft();
        break;
      case 'J':
        backwardRigth();
        break;
      case 'S':
        stop();
        break;
    }
  }
}

//Avanzar
void forward() {
  motorD1.setSpeed(255);
  motorD1.run(FORWARD);
  motorD2.setSpeed(255);
  motorD2.run(FORWARD);
  motorI1.setSpeed(255);
  motorI1.run(FORWARD);
  motorI2.setSpeed(255);
  motorI2.run(FORWARD);
}

//Avanzar izquierda
void forwardLeft() {
  motorD1.setSpeed(255);
  motorD1.run(FORWARD);
  motorD2.setSpeed(255);
  motorD2.run(FORWARD);
  motorI1.setSpeed(255 / 3.1);
  motorI1.run(FORWARD);
  motorI2.setSpeed(255 / 3.1);
  motorI2.run(FORWARD);
}

//Avanzar derecha
void forwardRight() {
  motorD1.setSpeed(255 / 3.1);
  motorD1.run(FORWARD);
  motorD2.setSpeed(255 / 3.1);
  motorD2.run(FORWARD);
  motorI1.setSpeed(255);
  motorI1.run(FORWARD);
  motorI2.setSpeed(255);
  motorI2.run(FORWARD);
}

//Retroceder
void backward() {
  motorD1.setSpeed(255);
  motorD1.run(BACKWARD);
  motorD2.setSpeed(255);
  motorD2.run(BACKWARD);
  motorI1.setSpeed(255);
  motorI1.run(BACKWARD);
  motorI2.setSpeed(255);
  motorI2.run(BACKWARD);
}

//Retroceder izquierda
void backwardLeft() {
  motorD1.setSpeed(255);
  motorD1.run(BACKWARD);
  motorD2.setSpeed(255);
  motorD2.run(BACKWARD);
  motorI1.setSpeed(255 / 3.1);
  motorI1.run(BACKWARD);
  motorI2.setSpeed(255 / 3.1);
  motorI2.run(BACKWARD);
}

//Retroceder derecha
void backwardRigth() {
  motorD1.setSpeed(255 / 3.1);
  motorD1.run(BACKWARD);
  motorD2.setSpeed(255 / 3.1);
  motorD2.run(BACKWARD);
  motorI1.setSpeed(255);
  motorI1.run(BACKWARD);
  motorI2.setSpeed(255);
  motorI2.run(BACKWARD);
}

//Girar a la izquierda
void left() {
  motorD1.setSpeed(255);
  motorD1.run(FORWARD);
  motorD2.setSpeed(255);
  motorD2.run(FORWARD);
  motorI1.setSpeed(255);
  motorI1.run(BACKWARD);
  motorI2.setSpeed(255);
  motorI2.run(BACKWARD);
}

//Girar a la derecha
void right() {
  motorD1.setSpeed(255);
  motorD1.run(BACKWARD);
  motorD2.setSpeed(255);
  motorD2.run(BACKWARD);
  motorI1.setSpeed(255);
  motorI1.run(FORWARD);
  motorI2.setSpeed(255);
  motorI2.run(FORWARD);
}

//Detener
void stop() {
  motorD1.setSpeed(0);
  motorD1.run(RELEASE);
  motorD2.setSpeed(0);
  motorD2.run(RELEASE);
  motorI1.setSpeed(0);
  motorI1.run(RELEASE);
  motorI2.setSpeed(0);
  motorI2.run(RELEASE);
}
