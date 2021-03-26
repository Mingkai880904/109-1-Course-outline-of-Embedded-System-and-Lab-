//#include <ESP8266WiFi.h>
#include <DHT.h>
#define DHTPIN D3

DHT dht(DHTPIN, DHT22);

void setup() {
  Serial.begin(115200);
  delay(10);
}

void loop() {
  float t;
  float h;
  t = dht.readTemperature();
  h = dht.readHumidity();
  
  while (isnan(h)){
    yield();
    h = dht.readHumidity();
    //return;
  }
  
  while (isnan(t)){
    yield();
    t = dht.readTemperature();
    //return;
  }

  String result = "s,";
  result += h;
  result += ",";
  result += t;
  result += ",e";

  Serial.println(result);

  delay(3000);
}
