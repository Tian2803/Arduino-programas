#include <AFMotor.h>
AF_DCMotor motorIzq(2, MOTOR12_64KHZ);
AF_DCMotor motorDer(4, MOTOR34_64KHZ);

float Kp = 1, Ki = 0.001, Kd = 1.1;
float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;
int initial_speed = 100;

#define NUM_SENSORES 5
int sensor[5] = { A0, A1, A2, A3, A4 };

void read_sensor_values(void);
void calculate_pid(void);
void motor_control(void);

void setup() {
  for (int i = 0; i < NUM_SENSORES; i++) {
    pinMode(sensor[i], INPUT);
  }
  Serial.begin(9600);
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

  if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[4] == 0) && (sensor[4] == 1))
    error = 4;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[4] == 1) && (sensor[4] == 1))
    error = 3;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[4] == 1) && (sensor[4] == 0))
    error = 2;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[4] == 1) && (sensor[4] == 0))
    error = 1;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[4] == 0) && (sensor[4] == 0))
    error = 0;
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[4] == 0) && (sensor[4] == 0))
    error = -1;
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[4] == 0) && (sensor[4] == 0))
    error = -2;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[4] == 0) && (sensor[4] == 0))
    error = -3;
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[4] == 0) && (sensor[4] == 0))
    error = -4;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[4] == 0) && (sensor[4] == 0))
    if (error == -4) error = -5;
    else error = 5;
}

void calculate_pid() {
  P = error;
  I = I + previous_I;
  D = error - previous_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D);

  previous_I = I;
  previous_error = error;
}

void motor_control() {
  //Se calcula la velocidad de los motores
  int left_motor_speed = initial_speed - PID_value;
  int right_motor_speed = initial_speed + PID_value;

  left_motor_speed = constrain(left_motor_speed, 0, 255);
  right_motor_speed = constrain(right_motor_speed, 0, 255);

  motorIzq.run(FORWARD);
  motorIzq.setSpeed(left_motor_speed);
  motorDer.run(FORWARD);
  motorDer.setSpeed(right_motor_speed);
}