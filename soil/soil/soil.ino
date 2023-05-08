#define SOIL_PIN A0 // analog pin for soil moisture sensor

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read soil moisture
  int soil_moisture = analogRead(SOIL_PIN);

  // print soil moisture value to serial monitor
  Serial.println(soil_moisture);

  // wait 200ms before taking the next measurement
  delay(500);
}
