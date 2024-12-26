//Sensores infrarrojos pines
/* const int sensorDerecho = 34;
const int sensorIzquierdo = 35; */

const int int1 = 12;
const int int2 = 14;
const int PWM_A = 18;

const int int3 = 27;
const int int4 = 26;
const int PWM_B = 5;

const int PWM_Chan1 = 0;
const int PWM_Chan2 = 1;
const int PWM_Freq = 30000;
const int PWM_Res = 8;
int speed = 255;

//Variables sensor ultrasonico
#define TRIG_PIN 4
#define ECHO_PIN 2
#define distMax 200

long duracion, distancia;

void setup() {
  // configuración de variables de los motores
  Serial.begin(115200);
  pinMode(PWM_A, OUTPUT);
  pinMode(int1, OUTPUT);
  pinMode(int2, OUTPUT);
  pinMode(PWM_B, OUTPUT);
  pinMode(int3, OUTPUT);
  pinMode(int4, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  /* pinMode(sensorDerecho, INPUT);
  pinMode(sensorIzquierdo, INPUT);
 */
  ledcAttachChannel(PWM_A, PWM_Freq, PWM_Res, PWM_Chan1);
  ledcAttachChannel(PWM_B, PWM_Freq, PWM_Res, PWM_Chan2);
}

void loop() {
  //Medir la distancia
  distancia = medirDistancia();

  //Robot busca oponente
  if (distancia >= 21) {
    digitalWrite(int1, HIGH);
    digitalWrite(int2, LOW);
    digitalWrite(int3, LOW);
    digitalWrite(int4, HIGH);
    ledcWrite(PWM_A, speed);
    ledcWrite(PWM_B, speed);
  }

  /* // Retroceder
  if (distancia >= 21 && (digitalRead(sensorIzquierdo) == 0 || digitalRead(sensorDerecho) == 0)) {
    digitalWrite(int1, LOW);
    digitalWrite(int2, HIGH);
    digitalWrite(int3, LOW);
    digitalWrite(int4, HIGH);
    ledcWrite(PWM_A, speed);
    ledcWrite(PWM_B, speed);
    delay(200);
  } */

  //Robot localiza oponente
  if (distancia <= 20) {
    digitalWrite(int1, HIGH);
    digitalWrite(int2, LOW);
    digitalWrite(int3, HIGH);
    digitalWrite(int4, LOW);
    ledcWrite(PWM_A, speed);
    ledcWrite(PWM_B, speed);
  }
}

int medirDistancia() {
  digitalWrite(TRIG_PIN, HIGH);
  delay(1);
  digitalWrite(TRIG_PIN, LOW);

  duracion = pulseIn(ECHO_PIN, HIGH); //Recibe el pulso
  int distanciaCM = duracion / 58.2;  // Realiza la conversion de la distancia a centímetros
  // Si la distancia es menor o igual a cero, o mayor o igual a 200, se considera como 200
  if (distanciaCM <= 0 || distanciaCM >= distMax) {
    distanciaCM = distMax;
  }
  return distanciaCM;  // Retorna la distancia medida
}