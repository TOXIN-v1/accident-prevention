const int sensorPin = 2;    // Connect the vibration sensor to digital pin 2
int vibrationState = 0;     // Variable to store the vibration state
int pulsePin = A0;          // Pulse sensor connected to analog pin A0
int threshold = 550;        // Adjust this threshold value based on your sensor
int sensorValue = 0;        // Variable to store the sensor value
int temp=0;

#include <SoftwareSerial.h>

SoftwareSerial gpsSerial(0, 1); // RX, TX for GPS module

void setup() {
  Serial.begin(9600);        // Initialize serial communication at 9600 bits per second
  gpsSerial.begin(9600);     // Initialize GPS serial communication at 9600 bits per second
  pinMode(sensorPin, INPUT); // Set the vibration sensor pin as input
}

void loop() {
  // Read the state of the vibration sensor
  vibrationState = digitalRead(sensorPin);
  sensorValue = analogRead(pulsePin);  // Read the sensor value

  // Check if vibration is detected
  if (vibrationState == HIGH) {
    Serial.println("Accident");
    getGPSLocation(); // Call the function to get GPS location
  }
  // Check if sensor value indicates stroke
  else if (sensorValue > threshold) {
    temp=sensorValue/5;
    if (temp>120){
      Serial.println("Stroke");
      if (gpsSerial.available() > 0) {
        if (gpsSerial.find("$GPRMC")) {
          String data = gpsSerial.readStringUntil('\n');
          Serial.println(data);
        }
      }
    }
  }
  else{
    Serial.println("nil");
  }
  delay(100);  // Delay for stability
}

void getGPSLocation() {
  if (gpsSerial.available() > 0) {
    if (gpsSerial.find("$GPRMC")) {
      String data = gpsSerial.readStringUntil('\n');
      Serial.println(data);
    }
  }
}
