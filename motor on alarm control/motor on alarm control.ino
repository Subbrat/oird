#include <Time.h>
#include <TimeAlarms.h>

int motorPin = 3;

void setup() {
  pinMode(motorPin, OUTPUT);
  setTime(7, 59, 55, 1, 1, 2023);  // Set time to January 1, 2023 12:00:00 AM
  Alarm.alarmRepeat(8, 0, 0, startMotor);  // Set alarm for 8:00:00 AM
  Alarm.alarmRepeat(8, 0, 10, stopMotor);   // Set alarm for 8:01:00 AM
  Serial.begin(9600);
}

void loop() {
  Alarm.delay(1000);
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.println(second());
}

void startMotor() {
  digitalWrite(motorPin, HIGH);
}

void stopMotor() {
  digitalWrite(motorPin, LOW);
}
