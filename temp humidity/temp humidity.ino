#include "DHT.h"                
#define DHTPIN 2          
#define DHTTYPE DHT11     
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 Testprogramm");
  dht.begin();
}
void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {       
    Serial.println("error reading sensor");
    return;
  }
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("Temperature: ");
  Serial.print(t);    
  Serial.write('°');  
  Serial.println("C");
}