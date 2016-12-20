#define FRONT_L_TRIG 32
#define FRONT_L_ECHO 33
#define FRONT_M_TRIG 24
#define FRONT_M_ECHO 23
#define FRONT_R_TRIG 30
#define FRONT_R_ECHO 31
#define BACK_L_TRIG 26
#define BACK_L_ECHO 27
#define BACK_M_TRIG 23
#define BACK_M_ECHO 22
#define BACK_R_TRIG 28
#define BACK_R_ECHO 29
#define FRONT_A_PWN 11
#define FRONT_IN_1 48
#define FRONT_IN_2 49
#define FRONT_B_PWN 10
#define FRONT_IN_3 46
#define FRONT_IN_4 47
#define BACK_A_PWN  13
#define BACK_IN_1 52
#define BACK_IN_2 53
#define BACK_B_PWN 12
#define BACK_IN_3 50
#define BACK_IN_4 51

void setup() {
  Serial.begin(9600);
  pinMode(FRONT_L_TRIG, OUTPUT);
  pinMode(FRONT_L_ECHO, INPUT);
  pinMode(FRONT_M_TRIG, OUTPUT);
  pinMode(FRONT_M_ECHO, INPUT);
  pinMode(FRONT_R_TRIG, OUTPUT);
  pinMode(FRONT_R_ECHO, INPUT);
  pinMode(BACK_L_TRIG, OUTPUT);
  pinMode(BACK_L_ECHO, INPUT);
  pinMode(BACK_M_TRIG, OUTPUT);
  pinMode(BACK_M_ECHO, INPUT);
  pinMode(BACK_R_TRIG, OUTPUT);
  pinMode(BACK_R_ECHO, INPUT);
  pinMode(BACK_IN_1, OUTPUT);
  pinMode(BACK_IN_2, OUTPUT);
  pinMode(BACK_IN_3, OUTPUT);
  pinMode(BACK_IN_4, OUTPUT);
  pinMode(FRONT_IN_1, OUTPUT);
  pinMode(FRONT_IN_2, OUTPUT);
  pinMode(FRONT_IN_3, OUTPUT);
  pinMode(FRONT_IN_4, OUTPUT);
}

void loop() {
  forward(255);
}
void decide() {
  //TODO implement this to decide which direction should be moved
  //store previous directions in an array of 3? so its not boring
}

void stopAll() {
  digitalWrite(BACK_IN_1, LOW);
  digitalWrite(BACK_IN_2, LOW);
  digitalWrite(BACK_IN_3, LOW);
  digitalWrite(BACK_IN_4, LOW);
  digitalWrite(FRONT_IN_1, LOW);
  digitalWrite(FRONT_IN_2, LOW);
  digitalWrite(FRONT_IN_3, LOW);
  digitalWrite(FRONT_IN_4, LOW);
}

void forwardLeft(int speed) {
  forwardForBackLeft(speed);
  forwardForFrontLeft(speed);
}

void forwardRight(int speed) {
  forwardForBackRight(speed);
  forwardForFrontRight(speed);
}

void backward(int speed) {
  backwardForBackLeft(speed);
  backwardForBackRight(speed);
  backwardForFrontLeft(speed);
  backwardForFrontRight(speed);
}

void backwardForBackLeft(int speed) {
  //enA and 1/2
  analogWrite(BACK_A_PWN, speed);
  digitalWrite(BACK_IN_2, LOW);
  digitalWrite(BACK_IN_1, HIGH);
}

void backwardForBackRight(int speed) {
  //enB and 3/4
  analogWrite(BACK_B_PWN, speed);
  digitalWrite(BACK_IN_4, HIGH);
  digitalWrite(BACK_IN_3, LOW);
}

void backwardForFrontLeft(int speed) {
  //enB and 3/4
  analogWrite(FRONT_A_PWN, speed);
  digitalWrite(FRONT_IN_2, HIGH);
  digitalWrite(FRONT_IN_1, LOW);
}

void backwardForFrontRight(int speed) {
  //enB and 3/4
  analogWrite(FRONT_B_PWN, speed);
  digitalWrite(FRONT_IN_4, LOW);
  digitalWrite(FRONT_IN_3, HIGH);
}

void forward(int speed) {
  forwardForBackLeft(speed);
  forwardForBackRight(speed);
  forwardForFrontLeft(speed);
  forwardForFrontRight(speed);
}

void forwardForBackLeft(int speed) {
  //enA and 1/2
  analogWrite(BACK_A_PWN, speed);
  digitalWrite(BACK_IN_1, LOW);
  digitalWrite(BACK_IN_2, HIGH);
}

void forwardForBackRight(int speed) {
  //enB and 3/4
  analogWrite(BACK_B_PWN, speed);
  digitalWrite(BACK_IN_3, HIGH);
  digitalWrite(BACK_IN_4, LOW);
}

void forwardForFrontLeft(int speed) {
  //enB and 3/4
  analogWrite(FRONT_A_PWN, speed);
  digitalWrite(FRONT_IN_1, HIGH);
  digitalWrite(FRONT_IN_2, LOW);
}

void forwardForFrontRight(int speed) {
  //enB and 3/4
  analogWrite(FRONT_B_PWN, speed);
  digitalWrite(FRONT_IN_3, LOW);
  digitalWrite(FRONT_IN_4, HIGH);
}

void checkFwdLeft() {
  checkDistance(FRONT_L_TRIG, FRONT_L_ECHO);
}

void checkFwdRight() {
  checkDistance(FRONT_R_TRIG, FRONT_R_ECHO);
}

void checkFwd() {
  checkDistance(FRONT_M_TRIG, FRONT_M_ECHO);
}

void checkBack() {
  checkDistance(BACK_M_TRIG, BACK_M_ECHO);
}

void checkBackLeft() {
  checkDistance(BACK_L_TRIG, BACK_L_ECHO);
}

void checkBackRight() {
  checkDistance(BACK_R_TRIG, BACK_R_ECHO);
}



int checkDistance(int trig, int echo) {//these are the pins you retard
  //ALWAYS HAVE A DELAY BEFORE CALLING THIS REPEATEDLY
  int cm;
  long duration;
  //should return the distance in cm
  // The sensor is triggered by a HIGH pulse of 10 or more miscroseconcs
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);

  // convert the time into a distance
  cm = (duration / 2) / 29.1;
  return cm;
}
