// Pin definitions for IR sensors
const int irLeft = 3;    // Left IR sensor
const int irRight = 4;   // Right IR sensor

// Pin definitions for ultrasonic sensor
const int trigPin = 6;   // Ultrasonic trigger pin
const int echoPin = 7;  // Ultrasonic echo pin

// Motor control pins
const int motorL1 = 8;   // Left motor forward
const int motorL2 = 9;   // Left motor backward
const int motorR1 = 10;   // Right motor forward
const int motorR2 = 11;   // Right motor backward

void setup() {
  pinMode(irLeft, INPUT);
  pinMode(irRight, INPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(motorL1, OUTPUT);
  pinMode(motorL2, OUTPUT);
  pinMode(motorR1, OUTPUT);
  pinMode(motorR2, OUTPUT);

  Serial.begin(9600); // Initialize Serial Monitor for debugging
}

void loop() {
  // Read IR sensors
  int leftIR = digitalRead(irLeft);
  int rightIR = digitalRead(irRight);
  Serial.print("IRL: ");
  Serial.println(leftIR);
  Serial.print("IRR: ");
  Serial.println(rightIR);
  // Measure distance using ultrasonic sensor
  long distance = getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);
  // Obstacle avoidance logic
  if (distance < 15) { // If an obstacle is closer than 15 cm
    stopMotors();
    delay(500); // Pause for a moment
    turnRight(); // Take a right turn to avoid the obstacle
    delay(500);
  } 
  // Line-following logic
  else {
    if (leftIR == 0 && rightIR == 1) { // Turn left
      turnLeft();
    } else if (leftIR == 1 && rightIR == 0) { // Turn right
      turnRight();
    } else if (leftIR == 1 && rightIR == 1) { // Go forward
      moveForward();
    } else { // Stop if no line detected
      stopMotors();
    }
  }

  delay(100); // Small delay to stabilize sensor readings
}

// Function to measure distance using the ultrasonic sensor
long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2; // Convert to cm
  return distance;
}

// Motor control functions
void moveForward() {
  digitalWrite(motorL1, HIGH);
  digitalWrite(motorL2, LOW);
  digitalWrite(motorR1, HIGH);
  digitalWrite(motorR2, LOW);
  Serial.println("Forward");
}

void turnLeft() {
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, LOW);
  digitalWrite(motorR1, HIGH);
  digitalWrite(motorR2, LOW);
  Serial.println("TurnLeft");
}

void turnRight() {
  digitalWrite(motorL1, HIGH);
  digitalWrite(motorL2, LOW);
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, LOW);
  Serial.println("TurnRight");
}

void stopMotors() {
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, LOW);
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, LOW);
  Serial.println("Stop");
}
