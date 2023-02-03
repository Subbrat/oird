const int sensorPin = A0;  // soil moisture sensor connected to analog pin A0
const int relayPin = 6;    // relay module connected to digital pin 6
const int ledPin = 13;     // onboard LED connected to digital pin 13
const int threshold = 700; // moisture level threshold

void setup() {
  pinMode(relayPin, OUTPUT);  // set the relay pin as an output
  pinMode(ledPin, OUTPUT);    // set the onboard LED pin as an output
  Serial.begin(9600);         // start serial communication at 9600 baud
}

void loop() {
  int sensorValue = analogRead(sensorPin);  // read the soil moisture value
  Serial.println(sensorValue);              // print the value to the serial monitor

  // turn on the motor if the soil is dry, and off if it's moist
  if (sensorValue > threshold) {
    digitalWrite(relayPin, LOW);
    digitalWrite(ledPin, HIGH);   // turn on the onboard LED while watering
  } else {
    digitalWrite(relayPin, HIGH);
    digitalWrite(ledPin, LOW);    // turn off the onboard LED when not watering
  }

  delay(1000);  // wait 1 second before reading again
}
