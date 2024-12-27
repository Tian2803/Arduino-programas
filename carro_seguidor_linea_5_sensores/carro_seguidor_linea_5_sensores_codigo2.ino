//Pines para los motores
int pwm_l = 9;      //PWM Pin 1
int pwm_r = 10;     //PWM Pin 2
int leftPin1 = 4;   //Left Motor Pin 1
int leftPin2 = 5;   //Left Motor Pin 2
int rightPin1 = 6;  //Right Motor Pin 1
int rightPin2 = 7;  //Right Motor Pin 2

float Kp = 1, Ki = 0.001, Kd = 1.1;
float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;
int initial_speed = 100;
int sensor[5] = { 0, 0, 0, 0, 0 };

void read_sensor_values(void);
void calculate_pid(void);
void motor_control(void);

void setup() {
  pinMode(pwm_l, OUTPUT);
  pinMode(pwm_r, OUTPUT);
  pinMode(leftPin1, OUTPUT);
  pinMode(leftPin2, OUTPUT);
  pinMode(rightPin1, OUTPUT);
  pinMode(rightPin2, OUTPUT);
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

  constrain(left_motor_speed, 0, 240);
  constrain(right_motor_speed, 0, 240);

  analogWrite(pwm_l, initial_speed - PID_value);   //Left Motor Speed
  analogWrite(pwm_r, initial_speed + PID_value);  //Right Motor Speed

  digitalWrite(leftPin1, HIGH);
  digitalWrite(leftPin2, LOW);
  digitalWrite(rightPin1, LOW);
  digitalWrite(rightPin2, HIGH);
}