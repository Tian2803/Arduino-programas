#include <AFMotor.h>

AF_DCMotor motorIzq(2, MOTOR12_64KHZ);
AF_DCMotor motorDer(4, MOTOR12_64KHZ);

#define NUM_SENSORES 5
int pinesSensores[NUM_SENSORES] = {A0, A1, A2, A3, A4};
int valoresSensores[NUM_SENSORES];
int umbral = 700;

void setup() {
  for (int i = 0; i < NUM_SENSORES; i++) {
    pinMode(pinesSensores[i], INPUT);
  }
}

void loop() {
  leerSensores();

  //All sensors detec then stop
  if( valoresSensores[0] > umbral && valoresSensores[1] > umbral && valoresSensores[2] > umbral && valoresSensores[3] > umbral && valoresSensores[4] > umbral){
    motorIzq.setSpeed(0);
    motorDer.setSpeed(0);
    motorIzq.run(RELEASE);
    motorDer.run(RELEASE);
    delay(1000);
    return;
  }
  else if (valoresSensores[4] > umbral) { // Sensor más derecho
    motorIzq.setSpeed(200);
    motorDer.setSpeed(150);
    motorIzq.run(FORWARD);
    motorDer.run(BACKWARD);
  } else if (valoresSensores[3] > umbral) { // Sensor derecho medio
    motorIzq.setSpeed(200);
    motorDer.setSpeed(0);
    motorIzq.run(FORWARD);
    motorDer.run(RELEASE);
  } else if (valoresSensores[2] > umbral) { // Sensor central
    motorIzq.setSpeed(200);
    motorDer.setSpeed(200);
    motorIzq.run(FORWARD);
    motorDer.run(FORWARD);
  } else if (valoresSensores[1] > umbral) { // Sensor izquierdo medio
    motorIzq.setSpeed(0);
    motorDer.setSpeed(200);
    motorIzq.run(RELEASE);
    motorDer.run(FORWARD);
  } else if (valoresSensores[0] > umbral) { // Sensor más izquierdo
    motorIzq.setSpeed(150);
    motorDer.setSpeed(200);
    motorIzq.run(BACKWARD);
    motorDer.run(FORWARD);
  } else { // Ningún sensor detecta la línea
    motorIzq.setSpeed(0);
    motorDer.setSpeed(0);
    motorIzq.run(RELEASE);
    motorDer.run(RELEASE);
  }
}

void leerSensores() {
  for (int i = 0; i < NUM_SENSORES; i++) {
    valoresSensores[i] = analogRead(pinesSensores[i]);
  }
}