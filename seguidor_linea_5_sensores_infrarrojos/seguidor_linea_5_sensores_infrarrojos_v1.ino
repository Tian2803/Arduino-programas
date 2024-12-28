//Pines para los motores
int ENA = 9;   //PWM Pin 1
int IN1 = 7;   //Right Motor Pin 1
int IN2 = 6;   //Right Motor Pin 2
int IN3 = 5;   //Left Motor Pin 1
int IN4 = 4;   //Left Motor Pin 2
int ENB = 10;  //PWM Pin 2

int speed = 200;
int pines[5] = { A0, A1, A2, A3, A4 };
int sensores[5] = { 0, 0, 0, 0, 0 };

bool salio_por_derecha = true;

void read_sensor_values(void);

void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  for (int i = 0; i < 5; i++) {
    pinMode(pines[i], INPUT);
  }
}

void loop() {
  read_sensor_values();

  Serial.print("Sensor 1: ");
  Serial.print(sensores[0]);
  Serial.print(" | Sensor 2: ");
  Serial.print(sensores[1]);
  Serial.print(" | Sensor 3: ");
  Serial.print(sensores[2]);
  Serial.print(" | Sensor 4: ");
  Serial.print(sensores[3]);
  Serial.print(" | Sensor 5: ");
  Serial.println(sensores[4]);

  //Sesnor del medio detecta linea negra
  if ((sensores[0] == 1) && (sensores[1] == 1) && (sensores[2] == 0) && (sensores[3] == 1) && (sensores[4] == 1)) {
    Serial.println("Forward");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, speed);  //Right Motor Speed
    analogWrite(ENB, speed);  //Left Motor Speed
  }

  // sensor izquierdo detecta linea negra
  if ((sensores[0] == 1) && (sensores[1] == 0) && (sensores[2] == 1) && (sensores[3] == 1) && (sensores[4] == 1)) {
    Serial.println("Turn left");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, speed);  //Right Motor Speed
    analogWrite(ENB, speed);  //Left Motor Speed
    salio_por_derecha = false;
  }

  //Sensor mas a la izquierda detecta linea negra
  if ((sensores[0] == 0) && (sensores[1] == 1) && (sensores[2] == 1) && (sensores[3] == 1) && (sensores[4] == 1)) {
    Serial.println("Turn left");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, speed);  //Right Motor Speed
    analogWrite(ENB, speed);  //Left Motor Speed
    salio_por_derecha = false;
  }

  // sensor derecho detecta linea negra
  if ((sensores[0] == 1) && (sensores[1] == 1) && (sensores[2] == 1) && (sensores[3] == 0) && (sensores[4] == 1)) {
    Serial.println("Turn right");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, speed);  //Right Motor Speed
    analogWrite(ENB, speed);  //Left Motor Speed
    salio_por_derecha = true;
  }

  //Sensor mas a la derecha detecta linea negra
  if ((sensores[0] == 1) && (sensores[1] == 1) && (sensores[2] == 1) && (sensores[4] == 1) && (sensores[4] == 0)) {
    Serial.println("Turn right");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, speed);  //Right Motor Speed
    analogWrite(ENB, speed);  //Left Motor Speed
    salio_por_derecha = true;
  }

  //Sensor del centro y el derecho detectan linea negra
  if ((sensores[0] == 1) && (sensores[1] == 1) && (sensores[2] == 0) && (sensores[3] == 0) && (sensores[4] == 1)) {
    Serial.println("Turn right");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, speed);  //Right Motor Speed
    analogWrite(ENB, speed);  //Left Motor Speed
    salio_por_derecha = true;
  }

  //Sensor del centro y el izquierdo detectan linea negra
  if ((sensores[0] == 1) && (sensores[1] == 0) && (sensores[2] == 0) && (sensores[3] == 1) && (sensores[4] == 1)) {
    Serial.println("Turn left");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, speed);  //Right Motor Speed
    analogWrite(ENB, speed);  //Left Motor Speed
    salio_por_derecha = false;
  }

  //Sensor del centro, el izquierdo y el mas a la izquierda detectan linea negra
  if ((sensores[0] == 0) && (sensores[1] == 0) && (sensores[2] == 0) && (sensores[3] == 1) && (sensores[4] == 1)) {
    Serial.println("Turn left");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, speed);  //Right Motor Speed
    analogWrite(ENB, speed);  //Left Motor Speed
    salio_por_derecha = false;
  }

  //Sensor del centro, el derecho y el mas a la derecha detectan linea negra
  if ((sensores[0] == 1) && (sensores[1] == 1) && (sensores[2] == 0) && (sensores[3] == 0) && (sensores[4] == 0)) {
    Serial.println("Turn right");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, speed);  //Right Motor Speed
    analogWrite(ENB, speed);  //Left Motor Speed
    salio_por_derecha = true;
  }

  //Sensor derecho y el mas a la derecha detectan linea negra
  if ((sensores[0] == 1) && (sensores[1] == 1) && (sensores[2] == 1) && (sensores[3] == 0) && (sensores[4] == 0)) {
    Serial.println("Turn right");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, speed);  //Right Motor Speed
    analogWrite(ENB, speed);  //Left Motor Speed
    salio_por_derecha = true;
  }

  //Sensor izquierdo y el mas a la izquierda detectan linea negra
  if ((sensores[0] == 0) && (sensores[1] == 0) && (sensores[2] == 1) && (sensores[3] == 1) && (sensores[4] == 1)) {
    Serial.println("Turn left");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, speed);  //Right Motor Speed
    analogWrite(ENB, speed);  //Left Motor Speed
    salio_por_derecha = false;
  }

  if ((sensores[0] == 1) && (sensores[1] == 1) && (sensores[2] == 1) && (sensores[3] == 1) && (sensores[4] == 1)) {
    if (salio_por_derecha) {
      Serial.println("Turn left");
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(ENA, speed / 2);
      analogWrite(ENB, speed / 2);
    } else {
      Serial.println("Turn right");
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(ENA, speed / 2);
      analogWrite(ENB, speed / 2);
    }
    return;
  }

  if ((sensores[0] == 0) && (sensores[1] == 0) && (sensores[2] == 0) && (sensores[3] == 0) && (sensores[4] == 0)) {
    //Stop
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
}

void read_sensor_values() {
  for (int i = 0; i < 5; i++) {
    sensores[i] = digitalRead(pines[i]);
  }
}