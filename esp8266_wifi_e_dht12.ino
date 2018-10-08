#include <ESP8266WiFi.h>
#include <DHT.h>
#define DHTTYPE   DHT11
#define DHTPIN    14 // D5

DHT dht(DHTPIN, DHTTYPE, 12);

float temperature, humidity;

const char* ssid="RIGON";
const char* password = "XXXXX";

void setup() {
  dht.begin();


  Serial.begin(115200);
  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println( ssid );

  WiFi.begin(ssid,password);

  Serial.println();
  Serial.print("Connecting");

  while( WiFi.status() != WL_CONNECTED ){
      delay(500);
      Serial.print(".");
  }


  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP() );

}

void loop() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  Serial.print("Umidade: ");
  Serial.println(humidity);
  Serial.print("Temperatura: ");
  Serial.println(temperature);
  delay(5000);

}
