#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

const int int1 = 12;
const int int2 = 14;
const int PWM_A = 4;

const int int3 = 27;
const int int4 = 26;
const int PWM_B = 5;

const int PWM_Chan1 = 0;
const int PWM_Chan2 = 1;
const int PWM_Freq = 30000;
const int PWM_Res = 8;
int speed = 170;    // Velocidad constante de los motores (valor PWM)
char receivedChar;  // Para almacenar el carácter recibido

void setup() {
  // Inicia la comunicación serie para la consola
  Serial.begin(115200);
  SerialBT.begin("Meteoro");  // Nombre del dispositivo Bluetooth
  pinMode(PWM_A, OUTPUT);
  pinMode(int1, OUTPUT);
  pinMode(int2, OUTPUT);
  pinMode(PWM_B, OUTPUT);
  pinMode(int3, OUTPUT);
  pinMode(int4, OUTPUT);

  ledcAttachChannel(PWM_A, PWM_Freq, PWM_Res, PWM_Chan1);
  ledcAttachChannel(PWM_B, PWM_Freq, PWM_Res, PWM_Chan2);
}

void loop() {
  while (SerialBT.available()) {
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
    case 'G':
      topleft();
      message = "Diagonal izquierda adelante";
      break;
    case 'I':
      topright();
      message = "Diagonal derecha adelante";
      break;
    case 'H':
      bottomleft();
      message = "Diagonal izquierda atras";
      break;
    case 'J':
      bottomright();
      message = "Diagonal derecha atras";
      break;
    case 'S':
      stop();
      message = "Detenido";
      break;
    case 'V':
      {
        // Ajuste de velocidad, asumiendo que la velocidad sigue al comando 'V'
        char speedChar[4];  // Para almacenar los 2 caracteres de la velocidad (por ejemplo: "12")
        int i = 0;
        while (SerialBT.available() && i < 4) {
          speedChar[i++] = (char)SerialBT.read();  // Leer los caracteres de velocidad
        }
        speedChar[i] = '\0';                  // Termina la cadena de velocidad
        int newSpeed = atoi(speedChar);       // Convierte los caracteres a un número entero
        speed = constrain(newSpeed, 0, 255);  // Limita el valor de la velocidad
        applySpeed();
        applySpeedLeft();
        applySpeedRight();
        message = "Velocidad ajustada a: " + String(speed);
        break;
      }
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
  /*   ledcWrite(PWM_A, speed);
  ledcWrite(PWM_B, speed); */
  applySpeed();
}

void backward() {
  digitalWrite(int1, LOW);
  digitalWrite(int2, HIGH);
  digitalWrite(int3, LOW);
  digitalWrite(int4, HIGH);
  applySpeed();
}

void right() {
  digitalWrite(int1, HIGH);
  digitalWrite(int2, LOW);
  digitalWrite(int3, LOW);
  digitalWrite(int4, HIGH);
  applySpeed();
}

void left() {
  digitalWrite(int1, LOW);
  digitalWrite(int2, HIGH);
  digitalWrite(int3, HIGH);
  digitalWrite(int4, LOW);
  applySpeed();
}

void topleft() {
  digitalWrite(int1, HIGH);
  digitalWrite(int2, LOW);
  digitalWrite(int3, HIGH);
  digitalWrite(int4, LOW);
  applySpeedLeft();
}

void topright() {
  digitalWrite(int1, HIGH);
  digitalWrite(int2, LOW);
  digitalWrite(int3, HIGH);
  digitalWrite(int4, LOW);
  applySpeedRight();
}

void bottomleft() {
  digitalWrite(int1, LOW);
  digitalWrite(int2, HIGH);
  digitalWrite(int3, LOW);
  digitalWrite(int4, HIGH);
  applySpeedLeft();
}

void bottomright() {
  digitalWrite(int1, LOW);
  digitalWrite(int2, HIGH);
  digitalWrite(int3, LOW);
  digitalWrite(int4, HIGH);
  applySpeedRight();
}

void stop() {
  digitalWrite(int1, LOW);
  digitalWrite(int2, LOW);
  digitalWrite(int3, LOW);
  digitalWrite(int4, LOW);
}

void applySpeed() {
  ledcWrite(PWM_A, speed);
  ledcWrite(PWM_B, speed);
}

void applySpeedLeft() {
  ledcWrite(PWM_A, speed / 1.7);
  ledcWrite(PWM_B, speed);
}

void applySpeedRight() {
  ledcWrite(PWM_A, speed);
  ledcWrite(PWM_B, speed / 1.7);
}
