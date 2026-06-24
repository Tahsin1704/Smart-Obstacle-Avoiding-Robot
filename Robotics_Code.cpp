#define trigPin 9
#define echoPin 10

#define buzzer 6
#define vibration 7

// Motor Driver Pins
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

long duration;
int distance;

void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(vibration, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  distance = getDistance();

  Serial.print("Distance: ");
  Serial.println(distance);

  // SAFE AREA
  if(distance > 80) {

    moveForward();

    digitalWrite(vibration, LOW);
    digitalWrite(buzzer, LOW);
  }

  // WARNING AREA
  else if(distance > 40) {

    moveForward();

    digitalWrite(vibration, HIGH);
    digitalWrite(buzzer, LOW);
  }

  // DANGER AREA
  else {

    stopRobot();

    digitalWrite(vibration, HIGH);
    digitalWrite(buzzer, HIGH);

    delay(500);

    avoidObstacle();
  }

  delay(100);
}

// FUNCTION TO GET DISTANCE
int getDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  int dist = duration * 0.034 / 2;

  return dist;
}

// MOVE FORWARD
void moveForward() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// STOP ROBOT
void stopRobot() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// TURN LEFT
void turnLeft() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  delay(700);

  stopRobot();
}

// TURN RIGHT
void turnRight() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  delay(700);

  stopRobot();
}

// OBSTACLE AVOIDANCE
void avoidObstacle() {

  stopRobot();

  delay(300);

  // First try left
  turnLeft();

  distance = getDistance();

  if(distance > 50) {

    moveForward();
  }

  else {

    // If left blocked, try right
    turnRight();
    turnRight();

    distance = getDistance();

    if(distance > 50) {

      moveForward();
    }

    else {

      stopRobot();

      digitalWrite(buzzer, HIGH);
    }
  }
}
