//Pines para los motores
int ENA = 9;   //PWM Pin 1
int IN1 = 7;   //Right Motor Pin 1
int IN2 = 6;   //Right Motor Pin 2
int IN3 = 5;   //Left Motor Pin 1
int IN4 = 4;   //Left Motor Pin 2
int ENB = 10;  //PWM Pin 2

float Kp = 1.5, Ki = 0.001, Kd = 0.5;  // 1 , 0.001,   1.1
float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;
int initial_speed = 100;
int sensor[5] = { 0, 0, 0, 0, 0 };

void read_sensor_values(void);
void calculate_pid(void);
void motor_control(void);

void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  read_sensor_values();
  calculate_pid();
  motor_control();
}

void read_sensor_values() {
  sensor[0] = digitalRead(A0);
  sensor[1] = digitalRead(A1);
  sensor[2] = digitalRead(A2);
  sensor[3] = digitalRead(A3);
  sensor[4] = digitalRead(A4);

  Serial.print("Sensor 1: ");
  Serial.print(sensor[0]);
  Serial.print(" | Sensor 2: ");
  Serial.print(sensor[1]);
  Serial.print(" | Sensor 3: ");
  Serial.print(sensor[2]);
  Serial.print(" | Sensor 4: ");
  Serial.print(sensor[3]);
  Serial.print(" | Sensor 5: ");
  Serial.print(sensor[4]);

  if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[4] == 1) && (sensor[4] == 0))
    error = 4;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0) && (sensor[4] == 0))
    error = 3;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0) && (sensor[4] == 1))
    error = 2;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 1))
    error = 1;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 1) && (sensor[4] == 1))
    error = 0;
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1) && (sensor[4] == 1))
    error = -1;
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1))
    error = -2;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1))
    error = -3;
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1))
    error = -4;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1))
    if (error == -4) error = -5;
    else error = 5;
}

void calculate_pid() {
  P = error;
  I += previous_I;
  D = error - previous_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D);

  previous_I = I;
  previous_error = error;
}

void motor_control() {
  //Se calcula la velocidad de los motores
  int left_motor_speed = initial_speed + PID_value;
  int right_motor_speed = initial_speed - PID_value;

  left_motor_speed = constrain(left_motor_speed, 0, 255);
  right_motor_speed = constrain(right_motor_speed, 0, 255);

  Serial.print(" | speed l: ");
  Serial.print(left_motor_speed);
  Serial.print(" | speed r: ");
  Serial.println(right_motor_speed);

  analogWrite(ENB, left_motor_speed);   //Left Motor Speed
  analogWrite(ENA, right_motor_speed);  //Right Motor Speed

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}