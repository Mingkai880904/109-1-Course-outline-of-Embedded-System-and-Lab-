#include <ESP8266WiFi.h>
#include <DHT.h>
#define DHTPIN D4

#define redLED D2
#define greenLED D3
#define blueLED D4

#define HOST "192.168.2.180"
const char* ssid = "ASUSLAB";
const char* password = "ASUSASUS";
DHT dht(DHTPIN, DHT22);
void setup() {
Serial.begin(115200);
delay(10);
Serial.println();
Serial.println();

pinMode(redLED,OUTPUT);   //LED腳位設為輸出
pinMode(greenLED,OUTPUT);
pinMode(blueLED,OUTPUT);
  
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
// Print the IP address
Serial.print("Your NodeMCU IP is : ");
Serial.print(WiFi.localIP());
}

void loop() {
float t;
float h;
t = dht.readTemperature();
h = dht.readHumidity();
while (isnan(h))
{
yield();
h = dht.readHumidity();
//return;
}
while (isnan(t))
{
yield();
t = dht.readTemperature();
//return;
}
Serial.println("-------------------");
Serial.print("溫度:");
Serial.println(t);
Serial.print("濕度:");
Serial.println(h);

WiFiClient client;
if (!client.connect(HOST,80)) {
Serial.println("connection failed");
Serial.println("wait 5 sec...");
delay(5000);
}
String dbserver = HOST;
String getStr = "GET /AddData.php?";
getStr +="Temp=";
getStr += String(t);
getStr +="&Humidity=";
getStr += String(h);
getStr += " HTTP/1.1\r\n";
getStr += "Host: " + String(dbserver) \
+ "\r\n"+ "Connection: close\r\n\r\n";

if (t<25)   
   {
      digitalWrite(redLED,LOW);  //點亮共陽型紅燈
      digitalWrite(greenLED,LOW);  //滅掉綠燈
      digitalWrite(blueLED,HIGH);
   }
  else if(t>= 25 & t<30)   //若 濕度未大於80%，則
   {  
      digitalWrite(redLED,LOW);     //滅掉紅燈
      digitalWrite(greenLED,HIGH);  //點亮綠燈
      digitalWrite(blueLED,LOW);
   }
   else{
      digitalWrite(redLED,HIGH);     //滅掉紅燈
      digitalWrite(greenLED,LOW);  //點亮綠燈
      digitalWrite(blueLED,LOW);
    
    }
    
client.print(getStr);
delay(10);
client.stop();
delay(3000);
}
