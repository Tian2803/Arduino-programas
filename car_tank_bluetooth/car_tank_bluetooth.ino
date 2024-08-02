#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

const int int1 = 12;
const int int2 = 14;
const int int3 = 27;
const int int4 = 26;

const int speed = 250;  // Velocidad constante de los motores (valor PWM)                         

void setup() {
  Serial.begin(115200);              // Inicia la comunicación serie para la consola
  SerialBT.begin("CarroBluetooth");  // Nombre del dispositivo Bluetooth
  pinMode(int1, OUTPUT);
  pinMode(int2, OUTPUT);
  pinMode(int3, OUTPUT);
  pinMode(int4, OUTPUT);
  digitalWrite(int1, LOW);
  digitalWrite(int2, LOW);
  digitalWrite(int3, LOW);
  digitalWrite(int4, LOW);
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();
    String message = executeCommand(command);
    Serial.println(message);  // Muestra el mensaje por la consola de depuración
  }
}

String executeCommand(char command) {
  String message;
  // Comandos para controlar el carro a través de Bluetooth
  switch (command) {
    case 'F':
      forward();
      message = "Moviendo hacia adelante";
      break;
    case 'B':
      backward();
      message = "Moviendo hacia atrás";
      break;
    case 'L':
      left();
      message = "Girando a la izquierda";
      break;
    case 'R':
      right();
      message = "Girando a la derecha";
      break;
    case 'S':
      stop();
      message = "Detenido";
      break;
    default:
      message = "Comando no reconocido";
      break;
  }
  return message;
}

void forward() {
  digitalWrite(int1, HIGH);
  digitalWrite(int2, LOW);
  digitalWrite(int3, HIGH);
  digitalWrite(int4, LOW);
}

void backward() {
  digitalWrite(int1, LOW);
  digitalWrite(int2, HIGH);
  digitalWrite(int3, LOW);
  digitalWrite(int4, HIGH);
}

void left() {
  digitalWrite(int1, HIGH);
  digitalWrite(int2, LOW);
  digitalWrite(int3, LOW);
  digitalWrite(int4, HIGH);
}

void right() {
  digitalWrite(int1, LOW);
  digitalWrite(int2, HIGH);
  digitalWrite(int3, HIGH);
  digitalWrite(int4, LOW);
}   

void stop() {
  digitalWrite(int1, LOW);                 
  digitalWrite(int2, LOW);
  digitalWrite(int3, LOW);
  digitalWrite(int4, LOW);
}          
