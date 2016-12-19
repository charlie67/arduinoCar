{
#define FRONT_L_TRIG
#define FRONT_L_ECHO
#define FRONT_M_TRIG 24
#define FRONT_M_ECHO 23
#define FRONT_R_TRIG
#define FRONT_R_ECHO
#define BACK_L_TRIG
#define BACK_L_ECHO
#define BACK_M_TRIG 23
#define BACK_M_ECHO 22
#define BACK_R_TRIG
#define BACK_R_ECHO
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
}
void setup() {
  //PWM pins dont need pinMode to be called
  Serial.begin(9600);
  //  pinMode(FRONT_L_TRIG, OUTPUT);
  //  pinMode(FRONT_L_ECHO, INPUT);
  pinMode(FRONT_M_TRIG, OUTPUT);
  pinMode(FRONT_M_ECHO, INPUT);
  //  pinMode(FRONT_R_TRIG, OUTPUT);
  //  pinMode(FRONT_R_ECHO, INPUT);
  //  pinMode(BACK_L_TRIG, OUTPUT);
  //  pinMode(BACK_L_ECHO, INPUT);
  pinMode(BACK_M_TRIG, OUTPUT);
  pinMode(BACK_M_ECHO, INPUT);
  //  pinMode(BACK_R_TRIG, OUTPUT);
  //  pinMode(BACK_R_ECHO, INPUT);
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
  forward(1000, 255);
  delay(1000);
}
void decide{
  //TODO implement this to decide which direction should be moved
  //store previous directions in an array of 3? so its not boring
}

void stopAll(){
  digitalWrite(BACK_IN_1, LOW);
  digitalWrite(BACK_IN_2, LOW);
  digitalWrite(BACK_IN_3, LOW);
  digitalWrite(BACK_IN_4, LOW);
  digitalWrite(FRONT_IN_1, LOW);
  digitalWrite(FRONT_IN_2, LOW);
  digitalWrite(FRONT_IN_3, LOW);
  digitalWrite(FRONT_IN_4, LOW);
}

void forward(int time, int speed) {
  forwardForBackLeft(speed);
  forwardForBackRight(speed);
  forwardForFrontLeft(speed);
  forwardForFrontRight(speed);
  delay(time);
  digitalWrite(BACK_IN_1, LOW);
  digitalWrite(BACK_IN_3, LOW);
  digitalWrite(FRONT_IN_1, LOW);
  digitalWrite(FRONT_IN_3, LOW);
}

void forwardForBackLeft(int speed) {
  //enA and 1/2
  analogWrite(BACK_A_PWN, speed);
  digitalWrite(BACK_IN_1, HIGH);
  digitalWrite(BACK_IN_2, LOW);
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
  digitalWrite(FRONT_IN_3, HIGH);
  digitalWrite(FRONT_IN_4, LOW);
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
