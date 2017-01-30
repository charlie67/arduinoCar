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
#define LEFT_TRIG 50
#define LEFT_ECHO 51
#define RIGHT_TRIG 6
#define RIGHT_ECHO 7
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

char previousDir;
char previousDirBefore;

void setup() {
  Serial.begin(9600);
  pinMode(LEFT_TRIG, OUTPUT);
  pinMode(LEFT_ECHO, INPUT);
  pinMode(RIGHT_TRIG, OUTPUT);
  pinMode(RIGHT_ECHO, INPUT);
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
}

void loop() {
  Serial.println("starting loop");
  standardRun();
}

void testSensors() {
  Serial.print("back Middle ");
  Serial.print(checkBack());
  Serial.print('\n');

  Serial.print("back Left ");
  Serial.print(checkBackLeft());
  Serial.print('\n');

  Serial.print("back right ");
  Serial.print(checkBackRight());
  Serial.print('\n');

  Serial.print("front Middle ");
  Serial.print(checkFwd());
  Serial.print('\n');

  Serial.print("front left ");
  Serial.print(checkFwdLeft());
  Serial.print('\n');

  Serial.print("front right ");
  Serial.print(checkFwdRight());
  Serial.print('\n');

  Serial.print("Left side");
  Serial.print(checkLeft());
  Serial.print('\n');

  Serial.print("Right side");
  Serial.print(checkRight());
  Serial.print('\n');
}

void drectionTestLoop() {
  forward(255);
  delay(2000);
  backward(255);
  delay(2000);
  turnLeft(255);
  delay(2000);
  turnRight(255);
  delay(2000);
}

void standardRun() {
  String dir = decide();
  previousDirBefore = previousDir;
  Serial.println(dir);
  while (carryOn(dir)) {
    if (dir == "forward") {
      previousDir = 'f';
      Serial.println("going forward");
      forward(255);
    } else if (dir == "back") {
      previousDir = 'b';
      Serial.println("going back");
      backward(255);
    } else if (dir == "left") {
      previousDir = 'l';
      Serial.println("going left");
      turnLeft(255);
    } else if (dir == "right") {
      previousDir = 'r';
      Serial.println("going right");
      turnRight(255);
    }
  }
  stopAll();
}

bool carryOn(String dir) {
  //only need to check the direction the car is moving
  if (dir == "forward") {

    if (checkFwd() < 10) {
      Serial.println("Can't continue checkFwd() detected object");
      return false;
    }

    else if (checkFwdLeft() < 10) {
      Serial.println("Can't continue checkFwdLeft() detected object");
      return false;
    }

    else if (checkFwdRight() < 10) {
      Serial.println("Can't continue checkFwdRight() detected object");
      return false;
    }

    else {
      Serial.println("all clear");
      return true;
    }
  } else if (dir == "back") {
    if (checkBack() < 10) {
      Serial.println("Can't continue checkBack() detected object");
      return false;
    }

    else if (checkBackLeft() < 10) {
      Serial.println("Can't continue checkBackLeft() detected object");
      return false;
    }

    else if (checkBackRight() < 10) {
      Serial.println("Can't continue checkBackRight() detected object");
      return false;
    }

    else {
      Serial.println("all clear");
      return true;
    }
  } else if (dir == "left") {
    //will want to stop when the front or back is clear or when the left side is blocked
    if (checkBack > 10 || checkBackLeft > 10 || checkBackRight > 10) {
      return false;
    } else if (checkLeft < 10 || checkRight < 10) {
      return false;
    } else if (checkFwdRight > 10 || checkFwdLeft > 10 || checkFwd > 10) {
      return false;
    } else {
      Serial.println("all clear");
      return true;
    }

  } else if (dir == "right") {
    if (checkBack > 10 || checkBackLeft > 10 || checkBackRight > 10) {
      return false;
    } else if (checkLeft < 10 || checkRight < 10) {
      return false;
    } else if (checkFwdRight > 10 || checkFwdLeft > 10 || checkFwd > 10) {
      return false;
    } else {
      Serial.println("all clear");
      return true;
    }
  }
}

String decide() {
  int forward = checkFwd();
  int back = checkBack();

  if ((previousDir == 'b' && previousDirBefore == 'f') || (previousDir == 'f' && previousDirBefore == 'b')) {
    Serial.println("gone forwards and then backwards seeing if I can turn");
    int left = checkLeft();
    int right = checkRight();

    if (left > right) {
      return "left";
    } else if (right > left) {
      return "right";
    }
  }
  
  if ((forward < 10 && back < 10) && (checkLeft() > 10 || checkRight() > 10)) {
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

    if (left > right && checkLeft > 10) {
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

int checkLeft() {
  return checkDistance(LEFT_TRIG, LEFT_ECHO);
}

int checkRight() {
  return checkDistance(RIGHT_TRIG, RIGHT_ECHO);
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
