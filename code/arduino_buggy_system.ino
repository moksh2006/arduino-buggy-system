/*
Hardware Connections

A0 -> Left IR Sensor
A1 -> Right IR Sensor
A2 -> Gantry IR Receiver

D13 -> Ultrasonic Trigger Pin
D12 -> Ultrasonic Echo Pin

D5  -> Left Motor Forward
D6  -> Left Motor Reverse

D8  -> Right Motor Forward
D7  -> Right Motor Reverse
*/

const int OBSTACLE_DISTANCE = 20;

int count = 0;
int leftSensor, rightSensor;

int flag = 0;

long st = millis(), endt;

const int trigPin = 13;
const int echoPin = 12;

int prevGantry = 0;

void setup() {
  Serial.begin(9600);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
}

void forward() {
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(7, LOW);
}

void left() {
  digitalWrite(8, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(7, LOW);
}

void right() {
  digitalWrite(8, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(7, LOW);
}

void stopMotors() {
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 20000);

  if (duration == 0)
    return -1;

  return duration * 0.0343 / 2;
}

void loop() {

  if (Serial.available() > 0 && Serial.read() == 'y') {
    flag = 1;
  }

  if (flag == 1) {

    // Gantry Detection
    int gantryPulse = pulseIn(A2, HIGH, 5000);

    if (gantryPulse >= 500 && gantryPulse < 1000 && prevGantry != 1) {
      Serial.println("Gantry 1 detected");
      stopMotors();
      delay(1000);
      prevGantry = 1;
    }

    else if (gantryPulse >= 1000 && gantryPulse < 2000 && prevGantry != 2) {
      Serial.println("Gantry 2 detected");
      stopMotors();
      delay(1000);
      prevGantry = 2;
    }

    else if (gantryPulse >= 2000 && gantryPulse < 3000 && prevGantry != 3) {
      Serial.println("Gantry 3 detected");
      stopMotors();
      delay(1000);
      prevGantry = 3;
    }

    // Obstacle Detection
    int distance = getDistance();

    if (distance != -1 && distance <= OBSTACLE_DISTANCE) {
      Serial.print("Obstacle at ");
      Serial.print(distance);
      Serial.println(" cm. Stopping.");

      stopMotors();
      delay(2000);
      return;
    }

    // Line Following
    leftSensor = digitalRead(A0);
    rightSensor = digitalRead(A1);

    if (leftSensor == 1 && rightSensor == 1)
      forward();

    else if (leftSensor == 0 && rightSensor == 1)
      left();

    else if (leftSensor == 1 && rightSensor == 0)
      right();

    else if (leftSensor == 0 && rightSensor == 0) {

      endt = millis();

      if (endt - st > 1000) {
        count++;
        st = millis();
      }

      switch (count) {

        case 1:
        case 3:
        case 4:
        case 6:
          Serial.print("Forward: ");
          Serial.println(count);
          forward();
          break;

        case 2:
          Serial.print("RIGHT Turn: ");
          Serial.println(count);
          right();
          delay(500);
          break;

        case 5:
          Serial.print("Right Turn: ");
          Serial.println(count);
          right();
          delay(300);
          break;

        case 7:
          Serial.print("Forward: ");
          Serial.println(count);
          forward();
          delay(300);
          break;

        default:
          stopMotors();
          Serial.println("Stopped");
          flag = 0;
          break;
      }
    }
  }
}
