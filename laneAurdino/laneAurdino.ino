#include <Mouse.h>
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
const int trigpin= 8;
const int echopin= 7;
const int vibrationPin = A1;
long duration;
int distance;
int sensorValue;
char command;
// Define the pin number for the IR sensor
const int leftIRSensor = 13;
const int rightIRSensor = 12;

void setup(){
  // Initialize Serial communication
  Serial.begin(9600);
  
  // Initialize the IR sensor pin as input
  pinMode(leftIRSensor, INPUT);
  pinMode(rightIRSensor, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
}

void loop() {

  // Debugging: print sensor values
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  duration = pulseIn(echopin, HIGH);
  distance = duration * 0.034 / 2;
  // Normal operation based on received commands
  switch(command) {
    case 'w': // Move forward if distance is greater than 10
      if (distance > 10){
        forward(); // Move forward only if distance is greater than 10
      } else {
        stopMotors(); // Stop if distance is less than or equal to 10
      }
      break;
    case 's': // Move backward
      backward();
      break;
    case 'a': // Turn left
      left();
      break;
    case 'd': // Turn right
      right();
      break;
    case 'x': // Stop
      stopMotors();
      break;
    case 'e':
      const int threshold = 600;
      int leftSensorValue = digitalRead(leftIRSensor);
      int rightSensorValue = digitalRead(rightIRSensor);
      Serial.println(leftSensorValue);
        // Lane detection
        if (leftSensorValue && rightSensorValue) {
          // If both sensors are on the line, move forward
          forward();
        } else if (leftSensorValue) {
          // If left sensor detects the line, turn right
          right();
        } else if (rightSensorValue) {
          // If right sensor detects the line, turn left
          left();
        } else {
          // If both sensors do not detect the lineeee, stopm 
          stopMotors();
        }
       break;

  }

  if (Serial.available() > 0) {
    command = Serial.read();
  }
  

}
void left() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void forward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}


