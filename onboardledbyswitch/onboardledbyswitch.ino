const int switchPin = 2;  // switch connected to digital pin 2

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  // set the built-in LED as an output
  pinMode(switchPin, INPUT);     // set the switch as an input
}

void loop() {
  if (digitalRead(switchPin) == LOW) {
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED on if switch is pressed
  } else {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED off if switch is not pressed
  }
}
