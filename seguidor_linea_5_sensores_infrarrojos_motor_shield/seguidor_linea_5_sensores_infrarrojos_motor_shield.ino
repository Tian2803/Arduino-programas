#include <AFMotor.h>
AF_DCMotor motorIzq(2, MOTOR12_64KHZ);
AF_DCMotor motorDer(4, MOTOR34_64KHZ);

int speed = 160;
int vh = speed + 40;
int vl = 0;

bool lastDirectionRight = false;  // Variable para recordar la última dirección del giro

#define NUM_SENSORES 5
int pinesSensores[NUM_SENSORES] = { A0, A1, A2, A3, A4 };
int valoresSensores[NUM_SENSORES];

void setup() {
  for (int i = 0; i < NUM_SENSORES; i++) {
    pinMode(pinesSensores[i], INPUT);
  }
}

void loop() {
  leerSensores();

  //Adelante
  if ((valoresSensores[0] == 0 && valoresSensores[1] == 0 && valoresSensores[2] == 1 && valoresSensores[3] == 0 && valoresSensores[4] == 0) || (valoresSensores[0] && valoresSensores[4])) {
    motorIzq.run(FORWARD);
    motorIzq.setSpeed(speed);
    motorDer.run(FORWARD);
    motorDer.setSpeed(speed);
  }

  //Adelante
  if (valoresSensores[0] == 0 && valoresSensores[1] == 1 && valoresSensores[2] == 1 && valoresSensores[3] == 1 && valoresSensores[4] == 0) {
    motorIzq.run(FORWARD);
    motorIzq.setSpeed(speed);
    motorDer.run(FORWARD);
    motorDer.setSpeed(speed);
  }

  //Girar a la derecha
  if (valoresSensores[0] == 0 && valoresSensores[1] == 0 && valoresSensores[2] == 0 && valoresSensores[3] == 0 && valoresSensores[4] == 1) {
    motorIzq.run(FORWARD);
    motorIzq.setSpeed(vh);
    motorDer.run(RELEASE);
    motorDer.setSpeed(vl);
    lastDirectionRight = true;  // Recordar que el último giro fue a la derecha
  }

  //Girar a la derecha sin deterne ningun motor
  if (valoresSensores[0] == 0 && valoresSensores[1] == 0 && valoresSensores[2] == 0 && valoresSensores[3] == 1 && valoresSensores[4] == 0) {
    motorIzq.run(FORWARD);
    motorIzq.setSpeed(vh);
    motorDer.run(FORWARD);
    motorDer.setSpeed(speed);
    lastDirectionRight = true;  // Recordar que el último giro fue a la derecha
  }

  //Girar a la derecha sin deterne ningun motor
  if (valoresSensores[0] == 0 && valoresSensores[1] == 0 && valoresSensores[2] == 0 && valoresSensores[3] == 1 && valoresSensores[4] == 1) {
    motorIzq.run(FORWARD);
    motorIzq.setSpeed(vh);
    motorDer.run(FORWARD);
    motorDer.setSpeed(speed);
    lastDirectionRight = true;  // Recordar que el último giro fue a la derecha
  }

  //Girar a la izquierda
  if (valoresSensores[0] == 1 && valoresSensores[1] == 0 && valoresSensores[2] == 0 && valoresSensores[3] == 0 && valoresSensores[4] == 0) {
    motorIzq.run(RELEASE);
    motorIzq.setSpeed(vl);
    motorDer.run(FORWARD);
    motorDer.setSpeed(speed);
    lastDirectionRight = false;  // Recordar que el último giro fue a la izquierda
  }

  //Girar a la izquierda sin deterne ningun motor
  if (valoresSensores[0] == 0 && valoresSensores[1] == 1 && valoresSensores[2] == 0 && valoresSensores[3] == 0 && valoresSensores[4] == 0) {
    motorIzq.run(FORWARD);
    motorIzq.setSpeed(speed);
    motorDer.run(FORWARD);
    motorDer.setSpeed(vh);
    lastDirectionRight = false;  // Recordar que el último giro fue a la izquierda
  }

  //Girar a la izquierda sin deterne ningun motor
  if (valoresSensores[0] == 1 && valoresSensores[1] == 1 && valoresSensores[2] == 0 && valoresSensores[3] == 0 && valoresSensores[4] == 0) {
    motorIzq.run(FORWARD);
    motorIzq.setSpeed(speed);
    motorDer.run(FORWARD);
    motorDer.setSpeed(vh);
    lastDirectionRight = false;  // Recordar que el último giro fue a la izquierda
  }

  //Ir hacia adelante con la velocidad de los motores diferentes - izquierda
  if (valoresSensores[0] == 0 && valoresSensores[1] == 1 && valoresSensores[2] == 1 && valoresSensores[3] == 0 && valoresSensores[4] == 0) {
    motorIzq.run(FORWARD);
    motorIzq.setSpeed(speed - 10);
    motorDer.run(FORWARD);
    motorDer.setSpeed(speed);
    lastDirectionRight = false;  // Recordar que el último giro fue a la izquierda
  }

  //Ir hacia adelante con la velocidad de los motores diferentes - derecha
  if (valoresSensores[0] == 0 && valoresSensores[1] == 0 && valoresSensores[2] == 1 && valoresSensores[3] == 1 && valoresSensores[4] == 0) {
    motorIzq.run(FORWARD);
    motorIzq.setSpeed(speed);
    motorDer.run(FORWARD);
    motorDer.setSpeed(speed - 10);
    lastDirectionRight = true;  // Recordar que el último giro fue a la derecha
  }

  //Todos detectan blanco (fuera de la línea)
  if (valoresSensores[0] == 0 && valoresSensores[1] == 0 && valoresSensores[2] == 0 && valoresSensores[3] == 0 && valoresSensores[4] == 0) {
    if (lastDirectionRight) {
      // Si se salió por la izquierda, girar a la derecha
      motorIzq.run(FORWARD);
      motorIzq.setSpeed(vh);
      motorDer.run(RELEASE);
      motorDer.setSpeed(vl);
    } else {
      motorIzq.run(RELEASE);
      motorIzq.setSpeed(vl);
      motorDer.run(FORWARD);
      motorDer.setSpeed(vh);
    }
  }

  //Si todos los sensores detectan negro se detiene el carro
  if (valoresSensores[0] == 1 && valoresSensores[1] == 1 && valoresSensores[2] == 1 && valoresSensores[3] == 1 && valoresSensores[4] == 1) {
    motorIzq.run(RELEASE);
    motorDer.run(RELEASE);
  }
}

void leerSensores() {
  for (int i = 0; i < NUM_SENSORES; i++) {
    valoresSensores[i] = analogRead(pinesSensores[i]);
    Serial.println(valoresSensores[i]);
  }
}