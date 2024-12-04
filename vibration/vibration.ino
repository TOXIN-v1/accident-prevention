const int vibrationPin = A0;  // Analog pin for vibration sensor
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   

//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED = LED_BUILTIN;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
                               
PulseSensorPlayground pulseSensor;
void setup() {
  Serial.begin(9600);  // Start serial communication
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 

}

void loop() {
  int sensorValue = analogRead(vibrationPin);  // Read sensor value
  if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened".
  int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                                // "myBPM" hold this BPM value now. 
                      // Print phrase "BPM: " 
    if (myBPM>120){
      Serial.println("stroke detected");
    }                        // Print the value inside of myBPM. 
    else if(sensorValue>800){
      Serial.println("Accident");
    } 
    else if (myBPM>120 && sensorValue>800){
      Serial.println("Both");
    }// Print sensor value to serial monitor
    delay(100);  // Delay for readability (adjust as needed)
  }
}