#include <AFMotor.h>
#include <Servo.h>

Servo baseServo;    // Servo para la base
Servo hombroServo;  // Servo para el hombro
Servo codoServo;    // Servo para el codo
Servo garraServo;   // Servo para la garra

char command;

void setup() {
  Serial.begin(9600);      //Set the baud rate to your Bluetooth module.
  baseServo.attach(11);    // Conecta el servo de la base al pin 11
  hombroServo.attach(10);  // Conecta el servo del hombro al pin 10
  codoServo.attach(9);     // Conecta el servo del codo al pin 9
  garraServo.attach(6);    // Conecta el servo de la garra al pin 6
  baseServo.write(90);     // Se inicie en 90 grados
  hombroServo.write(90);   // Se inicie en 90 grados
  codoServo.write(90);     // Se inicie en 90 grados
  garraServo.write(90);    // Se inicie en 90 grados
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();
    switch (command) {
      case 'F':  // Abrir la garra
        openGarra();
        break;
      case 'B':  // Cerrar la garra
        closeGarra();
        break;
      case 'R':  // Mover la base hacia adelante
        moveBaseForward();
        break;
      case 'L':  // Mover la base hacia atrás
        moveBaseBackward();
        break;
      case 'G':  // Mover el hombro hacia adelante
        moveHombroForward();
        break;
      case 'I':  // Mover el hombro hacia atrás
        moveHombroBackward();
        break;
      case 'H':  // Mover el codo hacia adelante
        moveCodoForward();
        break;
      case 'J':  // Mover el codo hacia atrás
        moveCodoBackward();
        break;
    }
  }
}

void openGarra() {
  garraServo.write(garraServo.read() + 1);
}

void closeGarra() {
  garraServo.write(garraServo.read() - 1);  // Ajusta la posición del servo para cerrar la garra
}

void moveBaseForward() {
  baseServo.write(baseServo.read() + 1);
}

void moveBaseBackward() {
  baseServo.write(baseServo.read() - 1);
}

void moveHombroForward() {
  hombroServo.write(hombroServo.read() + 1);  // Ajusta la posición del servo del hombro hacia adelante
}

void moveHombroBackward() {
  hombroServo.write(hombroServo.read() - 1);  // Ajusta la posición del servo del hombro hacia atrás
}

void moveCodoForward() {
  codoServo.write(codoServo.read() + 1);  // Ajusta la posición del servo del codo hacia adelante
}

void moveCodoBackward() {
  codoServo.write(codoServo.read() - 1);  // Ajusta la posición del servo del codo hacia atrás
}