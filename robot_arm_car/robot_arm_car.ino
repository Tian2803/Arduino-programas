#include <AFMotor.h>
#include <Servo.h>

//Inicializacion, pin de motores
AF_DCMotor motorI1(1, MOTOR12_1KHZ);
AF_DCMotor motorI2(4, MOTOR12_1KHZ);
AF_DCMotor motorD1(2, MOTOR12_1KHZ);
AF_DCMotor motorD2(3, MOTOR12_1KHZ);

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
  baseServo.write(90);
  hombroServo.write(90);
  codoServo.write(90);
  garraServo.write(90);
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();
    stop();  //initialize with motors stoped
    //Change pin mode only if new command is different from previous.
    //Serial.println(command);
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
      case 'G':  // Abrir la garra
        openGarra();
        break;
      case 'I':  // Cerrar la garra
        closeGarra();
        break;
      case 'H':  // Mover la base hacia adelante
        moveBaseForward();
        break;
      case 'J':  // Mover la base hacia atrás
        moveBaseBackward();
        break;
      case '3':  // Mover el hombro hacia adelante
        moveHombroForward();
        break;
      case '4':  // Mover el hombro hacia atrás
        moveHombroBackward();
        break;
      case '5':  // Mover el codo hacia adelante
        moveCodoForward();
        break;
      case '6':  // Mover el codo hacia atrás
        moveCodoBackward();
        break;
    }
  }
}

void forward() {
  motorD1.setSpeed(255);  //Define maximum velocity|
  motorD1.run(FORWARD);   //rotate the motor clockwise
  motorD2.setSpeed(255);  //Define maximum velocity|
  motorD2.run(FORWARD);   //rotate the motor clockwise
  motorI1.setSpeed(255);  //Define maximum velocity
  motorI1.run(FORWARD);   //rotate the motor clockwise
  motorI2.setSpeed(255);  //Define maximum velocity
  motorI2.run(FORWARD);   //rotate the motor clockwise
}

void backward() {
  motorD1.setSpeed(255);  //Define maximum velocity|
  motorD1.run(BACKWARD);  //rotate the motor clockwise
  motorD2.setSpeed(255);  //Define maximum velocity|
  motorD2.run(BACKWARD);  //rotate the motor clockwise
  motorI1.setSpeed(255);  //Define maximum velocity
  motorI1.run(BACKWARD);  //rotate the motor clockwise
  motorI2.setSpeed(255);  //Define maximum velocity
  motorI2.run(BACKWARD);  //rotate the motor clockwise
}

void left() {
  motorD1.setSpeed(255);  //Define maximum velocity|
  motorD1.run(FORWARD);   //rotate the motor clockwise
  motorD2.setSpeed(255);  //Define maximum velocity|
  motorD2.run(FORWARD);   //rotate the motor clockwise
  motorI1.setSpeed(255);  //Define maximum velocity
  motorI1.run(BACKWARD);  //rotate the motor clockwise
  motorI2.setSpeed(255);  //Define maximum velocity
  motorI2.run(BACKWARD);  //rotate the motor clockwise
}

void right() {
  motorD1.setSpeed(255);  //Define maximum velocity|
  motorD1.run(BACKWARD);  //rotate the motor clockwise
  motorD2.setSpeed(255);  //Define maximum velocity|
  motorD2.run(BACKWARD);  //rotate the motor clockwise
  motorI1.setSpeed(255);  //Define maximum velocity
  motorI1.run(FORWARD);   //rotate the motor clockwise
  motorI2.setSpeed(255);  //Define maximum velocity
  motorI2.run(FORWARD);   //rotate the motor clockwise
}

void stop() {
  motorD1.setSpeed(0);   //Define minimum velocity
  motorD1.run(RELEASE);  //stop the motor when release the button
  motorD2.setSpeed(0);   //Define minimum velocity
  motorD2.run(RELEASE);  //stop the motor when release the button
  motorI1.setSpeed(0);   //Define minimum velocity
  motorI1.run(RELEASE);  //rotate the motor clockwise
  motorI2.setSpeed(0);   //Define minimum velocity
  motorI2.run(RELEASE);  //rotate the motor clockwise
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
