#include <DHT.h>
#include <string.h>
#include <stdio.h>

const int sensorPin = A0;
const int relayPin = 6;
const int ledPin = 13;
const int threshold = 700;
const int temperatureThreshold = 30; // temperature threshold in degrees Celsius
const int dhtPin = 2;
const int dhtType = DHT11;

DHT dht(dhtPin, dhtType);
unsigned long startTime;
unsigned long currentTime;

void setup() {
pinMode(relayPin, OUTPUT);
pinMode(ledPin, OUTPUT);
Serial.begin(9600);
dht.begin();
}
void loop() {
  int sensorValue = analogRead(sensorPin);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("error reading sensor");
    return;
  }

  if (sensorValue > threshold) {
    digitalWrite(relayPin, LOW);
    digitalWrite(ledPin, HIGH);
    startTime = millis();
    while (sensorValue > threshold) {
      unsigned long elapsedTime = (millis() - startTime) / 1000;
      Serial.print("In Use Since: ");
      Serial.print(elapsedTime / 60);
      Serial.print(":");
      Serial.print(elapsedTime % 60);
      Serial.print(" Moisture Level: " + String(sensorValue));
      Serial.print(" Humidity: " + String(humidity) + "%");
      Serial.print(" Temperature: " + String(temperature) + "°C");
      if (temperature >= temperatureThreshold) {
        Serial.println(" Watering 10% more due to high temperature");
      } else {
        Serial.println();
      }
      delay(1000);
      // Add delay after reading values
      delay(1000);
      sensorValue = analogRead(sensorPin);
    }
    Serial.print("Moisture Level: " + String(sensorValue));
    Serial.println(" Motor turned off");
  } else {
    digitalWrite(relayPin, HIGH);
    digitalWrite(ledPin, LOW);
    Serial.print(" Moisture Level: " + String(sensorValue));
    Serial.print(" Humidity: " + String(humidity) + "%");
    Serial.println(" Temperature: " + String(temperature) + "°C");
    delay(1000);
  }
}
