#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Pin definitions
#define DHT_PIN 2
#define MOISTURE_PIN A0
#define WATER_MOTOR_PIN 5
#define LED_LIGHTS_PIN 6
#define MANUAL_CONTROL_BUTTON_PIN_1 7   

#define MANUAL_CONTROL_BUTTON_PIN_2 8
#define SPEED_CONTROL_PIN 9

// Thresholds for environmental conditions
#define MOISTURE_THRESHOLD 600
#define TEMPERATURE_THRESHOLD 25
#define HUMIDITY_THRESHOLD 60

// Constants for the DHT library
#define DHT_TYPE DHT11
#define DHT_DELAY 1000

// Instance of the DHT library
DHT dht(DHT_PIN, DHT_TYPE);

// Instance of the RTC library
RTC_DS3231 rtc;

// Variables to store the environmental conditions
float temperature;
float humidity;
int moisture;

// Variables to store the state of the actuators
bool waterMotorOn = false;
bool ledLightsOn = false;
int motorSpeed = 0;

// Variables to store the state of the manual control buttons
bool manualControlButton1 = false;
bool manualControlButton2 = false;

// Variables to store the time of the last water motor and LED light events
unsigned long waterMotorStartTime = 0;
unsigned long waterMotorDuration = 5000; // 5 seconds
unsigned long ledLightsStartTime = 0;

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Initialize the DHT library
  dht.begin();

  // Initialize the RTC library
  if (! rtc.begin()) {
    Serial.println("Could not find RTC");
    while (1);
  }

  // Set the initial state of the manual control buttons
  manualControlButton1 = digitalRead(MANUAL_CONTROL_BUTTON_PIN_1);
  manualControlButton2 = digitalRead(MANUAL_CONTROL_BUTTON_PIN_2);

  // Set the pin modes for the actuators
  pinMode(WATER_MOTOR_PIN, OUTPUT);
  pinMode(LED_LIGHTS_PIN, OUTPUT);
  pinMode(SPEED_CONTROL_PIN, INPUT);

  // Set the pin modes for the manual control buttons
  pinMode(MANUAL_CONTROL_BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(MANUAL_CONTROL_BUTTON_PIN_2, INPUT_PULLUP);
}

void loop() {
  // Read the environmental conditions
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  moisture = analogRead(MOISTURE_PIN);

  // Read the state of the manual control buttons
  manualControlButton1 = digitalRead(MANUAL_CONTROL_BUTTON_PIN_1);
  manualControlButton2 = digitalRead(MANUAL_CONTROL_BUTTON_PIN_2);

  // Automated control based on environmental conditions
  if (moisture < MOISTURE_THRESHOLD && !waterMotorOn) {
    waterMotorOn = true;
    digitalWrite(WATER_MOTOR_PIN, HIGH);
    waterMotorStartTime = millis();
    Serial.println("Water motor turned on (Automated)");
  }
  if (temperature > TEMPERATURE_THRESHOLD && !ledLightsOn) {
    ledLightsOn = true;
    digitalWrite(LED_LIGHTS_PIN, HIGH);
    ledLightsStartTime = millis();
    Serial.println("LED lights turned on (Automated)");
  }

  // Manual control based on buttons
  if (!manualControlButton1 && ledLightsOn) {
    ledLightsOn = false;
    digitalWrite(LED_LIGHTS_PIN, LOW);
    Serial.println("LED lights turned off (Manual)");
  }
  if (!manualControlButton2 && waterMotorOn) {
    waterMotorOn = false;
    digitalWrite(WATER_MOTOR_PIN, LOW);
    Serial.println("Water motor turned off (Manual)");
  }

  // Check if the water motor has been on for the specified duration
  if (waterMotorOn && millis() - waterMotorStartTime >= waterMotorDuration) {
    waterMotorOn = false;
    digitalWrite(WATER_MOTOR_PIN, LOW);
    Serial.println("Water motor turned off (Duration)");
  }

  // Update the motor speed based on the input from the website
  motorSpeed = analogRead(SPEED_CONTROL_PIN);

  // Output the environmental conditions and actuator state to the serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C\t");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Moisture: ");
  Serial.print(moisture);
  Serial.print("\t");
  Serial.print("Water Motor: ");
  Serial.print(waterMotorOn ? "ON" : "OFF");
  Serial.print("\t");
  Serial.print("LED Lights: ");
  Serial.print(ledLightsOn ? "ON" : "OFF");
  Serial.print("\t");
  Serial.print("Motor Speed: ");
  Serial.println(motorSpeed);

  // Delay to allow the DHT library to settle
  delay(DHT_DELAY);
}
