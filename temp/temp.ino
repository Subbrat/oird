const int sensorPin = A0;  // soil moisture sensor connected to analog pin A0
const int relayPin = 6;    // relay module connected to digital pin 6
const int ledPin = 13;     // onboard LED connected to digital pin 13
const int threshold = 700; // moisture level threshold
unsigned long startTime;    // variable to store start time of motor
unsigned long currentTime;  // variable to store current time

void setup() {
  pinMode(relayPin, OUTPUT);  // set the relay pin as an output
  pinMode(ledPin, OUTPUT);    // set the onboard LED pin as an output
  Serial.begin(9600);         // start serial communication at 9600 baud
}

void loop() {
  int sensorValue = analogRead(sensorPin);  // read the soil moisture value

  // turn on the motor if the soil is dry, and off if it's moist
  if (sensorValue > threshold) {
    digitalWrite(relayPin, LOW);
    digitalWrite(ledPin, HIGH);   // turn on the onboard LED while watering
    startTime = millis();          // store the start time of the motor

    while (sensorValue > threshold) {  // display time since last use while motor is on
      unsigned long elapsedTime = (millis() - startTime) / 1000;
      if (elapsedTime < 60) {
        Serial.println("In Use Since: " + String(elapsedTime) + " sec");
      } else {
        Serial.println("In Use Since: " + String(elapsedTime / 60) + " min");
      }
      delay(1000);  // wait 1 second before reading again
      sensorValue = analogRead(sensorPin);  // read the soil moisture value again
    }
    Serial.println("Motor turned off");
  } else {
    digitalWrite(relayPin, HIGH);
    digitalWrite(ledPin, LOW);    // turn off the onboard LED when not watering
    delay(1000);  // wait 1 second before reading again
  }
}