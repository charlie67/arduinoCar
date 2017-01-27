#include "SoftwareSerial.h"
SoftwareSerial BT(52, 53);

bool canRun = false;

#define FRONT_L_TRIG 32
#define FRONT_L_ECHO 33
#define FRONT_M_TRIG 34
#define FRONT_M_ECHO 35
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
#define BACK_IN_1 43
#define BACK_IN_2 41
#define BACK_B_PWN 12
#define BACK_IN_3 45
#define BACK_IN_4 44

void setup() {
  BT.begin(9600);
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
  pinMode(13, OUTPUT);

  delay(3000);//delay to connect via BT
}

void loop() {
  BT.println("starting loop");
  standardRun(255);
}

void standardRun(int speed) {
  String dir = decide();
  BT.println(dir);
  while (carryOn(dir)) {
    if (dir == "forward") {
      forward(speed);
    } else if (dir == "back") {
      backward(speed);
    } else if (dir == "left") {
      turnLeft(speed);
      delay(15);
    } else if (dir == "right") {
      turnRight(speed);
      delay(15);
    }
    stopAll();
  }
}

bool carryOn(String dir) {
  //only need to check the direction the car is moving
  if (dir == "forward") {

    if (checkFwd() < 20) {
      BT.println("checkFwd() detected object");
      return false;
    }

    else if (checkFwdLeft() < 20) {
      BT.println("checkFwdLeft() detected object");
      return false;
    }

    else if (checkFwdRight() < 20) {
      BT.println("checkFwdRight() detected object");
      return false;
    }

    else {
      return true;
    }
  } else if (dir == "back") {
    if (checkBack() < 20) {
      BT.println("checkBack() detected object");
      return false;
    }

    else if (checkBackLeft() < 20) {
      BT.println("checkBackLeft() detected object");
      return false;
    }

    else if (checkBackRight() < 20) {
      BT.println("checkBackRight() detected object");
      return false;
    }

    else {
      return true;
    }
  }
}

String decide() {
  int forward = checkFwd();
  int back = checkBack();
  if (forward < 20 && back < 20) {
    /*will have to turn
      decide which direction

      frontLeft and backright go together
      as do backleft and frontRight
      so we can start by checking those
    */
    //turning left
    int frontLeft = checkFwdLeft();
    int backRight = checkBackRight();
    int left = (frontLeft + backRight) / 2;

    //turning right
    int frontRight = checkFwdRight();
    int backLeft = checkBackLeft();
    int right = (frontRight + backLeft) / 2;

    if (left > right) {
      return "left";
    } else {
      return "right";
    }
  }
  else if (forward > back) {
    return "forward";
  } else if (back > forward) {
    return "back";
  } else {
    return "forward";
  }
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

void turnLeft(int speed) {//going forwards
  //a delay of 675 turns it 90 degrees at a speed of 255
  forwardLeft(255);
  backwardRight(255);
}

void turnRight(int speed) {//going forwards
  forwardRight(speed);
  backwardLeft(speed);
}

void backwardRight(int speed) { //moves the right side backwards
  backwardForFrontRight(speed);
  backwardForBackRight(speed);
}

void backwardLeft(int speed) { //moves left side backwards
  backwardForBackLeft(speed);
  backwardForBackRight(speed);
}

void forwardLeft(int speed) {//moves left forwards
  forwardForBackLeft(speed);
  forwardForFrontLeft(speed);
}

void forwardRight(int speed) {//moves right forwards
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

int checkFwdLeft() {
  return checkDistance(FRONT_L_TRIG, FRONT_L_ECHO);
}

int checkFwdRight() {
  return checkDistance(FRONT_R_TRIG, FRONT_R_ECHO);
}

int checkFwd() {
  return checkDistance(FRONT_M_TRIG, FRONT_M_ECHO);
}

int checkBack() {
  return checkDistance(BACK_M_TRIG, BACK_M_ECHO);
}

int checkBackLeft() {
  return checkDistance(BACK_L_TRIG, BACK_L_ECHO);
}

int checkBackRight() {
  return checkDistance(BACK_R_TRIG, BACK_R_ECHO);
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
