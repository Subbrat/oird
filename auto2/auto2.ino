#include "DHT.h"    
#define DHTTYPE DHT11;
const int relayPin = 6;
const int moistureSensorPin = A0;
const int dhtSensorPin = 2;
const int targetMoisture = 400;  // adjust this value to suit your needs
const int wateringDuration = 6000;  // 6 seconds

int currentMoisture = 0;
float temperature = 0.0;
float humidity = 0.0;

void setup() {
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  currentMoisture = analogRead(moistureSensorPin);
  if (currentMoisture < targetMoisture) {
    water();
  }
  
  // Read the humidity and temperature values from the DHT sensor
  int readResult = DHT.read11(dhtSensorPin);
  if (readResult == DHTLIB_OK) {
    temperature = DHT.temperature;
    humidity = DHT.humidity;
  }
  
  if (temperature > 30.0) {
    int adjustedDuration = wateringDuration + (wateringDuration * 0.1);
    waterForDuration(adjustedDuration);
  }
}

void water() {
  digitalWrite(relayPin, HIGH);  // turn on the relay
  delay(wateringDuration);  // wait for the specified duration
  digitalWrite(relayPin, LOW);  // turn off the relay
}

void waterForDuration(int duration) {
  digitalWrite(relayPin, HIGH);  // turn on the relay
  delay(duration);  // wait for the specified duration
  digitalWrite(relayPin, LOW);  // turn off the relay
}
