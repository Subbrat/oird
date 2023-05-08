const int sensorPin = A0;
const int relayPin = 6;
const int ledPin = 13;
const int threshold = 700;
unsigned long startTime;
unsigned long currentTime;
void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  int sensorValue = analogRead(sensorPin);
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
      Serial.println("  Moisture Level: " + String(sensorValue));
      delay(1000);
      sensorValue = analogRead(sensorPin);
    }
    Serial.print("Moisture Level: " + String(sensorValue));
    Serial.println("  Motor turned off");
  } else {
    digitalWrite(relayPin, HIGH);
    digitalWrite(ledPin, LOW);
    Serial.println("  Moisture Level: " + String(sensorValue));
    delay(1000);
  }
}
