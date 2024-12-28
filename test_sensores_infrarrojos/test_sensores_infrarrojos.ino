// Pines para los 5 sensores infrarrojos
const int sensor1 = A0;  // Sensor 1 conectado a A0
const int sensor2 = A1;  // Sensor 2 conectado a A1
const int sensor3 = A2;  // Sensor 3 conectado a A2
const int sensor4 = A3;  // Sensor 4 conectado a A3
const int sensor5 = A4;  // Sensor 5 conectado a A4

void setup() {
  // Inicializa la comunicación serial
  Serial.begin(9600);

  // Configura los pines como entrada
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);

  // Mensaje de inicio
  Serial.println("Leyendo 5 sensores infrarrojos...");
}

void loop() {
  // Lee los valores de los sensores
  int lectura1 = digitalRead(sensor1);
  int lectura2 = digitalRead(sensor2);
  int lectura3 = digitalRead(sensor3);
  int lectura4 = digitalRead(sensor4);
  int lectura5 = digitalRead(sensor5);

  // Muestra las lecturas en el monitor serial
  Serial.print("Sensor 1: "); Serial.print(lectura1);
  Serial.print(" | Sensor 2: "); Serial.print(lectura2);
  Serial.print(" | Sensor 3: "); Serial.print(lectura3);
  Serial.print(" | Sensor 4: "); Serial.print(lectura4);
  Serial.print(" | Sensor 5: "); Serial.println(lectura5);

  // Espera 500 ms antes de la siguiente lectura
  delay(500);
}
