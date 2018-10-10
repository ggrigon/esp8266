#include <ESP8266WiFi.h>
#include <DHT12.h>

DHT12 dht12(14, true);
WiFiClient client;

float temperature, humidity, heatindex, dewpoint;

const char* ssid="XXXXX";
const char* password = "XXXXX";



String apiKey = "XXXXX";
const char* server = "api.thingspeak.com";


void setup() {
  dht12.begin();
  Serial.begin(9600);
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
  humidity = dht12.readHumidity();
  temperature = dht12.readTemperature();
  heatindex = dht12.computeHeatIndex(temperature, humidity, false);
  dewpoint = dht12.dewPoint(temperature, humidity, false);
  
   //Inicia um client TCP para o envio dos dados
  if (client.connect(server,80)) {
    String postStr = apiKey;
           postStr +="&amp;field1=";
           postStr += String(temperature);
           postStr +="&amp;field2=";
           postStr += String(humidity);
           postStr +="&amp;field3=";
           postStr += String(heatindex);
           postStr +="&amp;field4=";
           postStr += String(dewpoint);
           //postStr += "\r\n\r\n";
 
     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(postStr.length());
     client.print("\n\n");
     client.print(postStr);
 
     //Logs na porta serial
      Serial.print("DHT12=> Temperatura: ");
      Serial.print(temperature);
      Serial.print("C ");
      Serial.print("Umidade: ");
      Serial.print(humidity);
      Serial.print("% ");
      Serial.print("Índice de Calor: ");
      Serial.print(heatindex);
      Serial.print("C ");
      Serial.print("Ponto de orvalho: ");
      Serial.print(dewpoint);
      Serial.println("C");
     
  }
  client.stop();
  delay(60000);
}
