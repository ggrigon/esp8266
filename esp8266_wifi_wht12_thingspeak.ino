#include <ESP8266WiFi.h>
#include <DHT.h>
#define DHTTYPE   DHT11
#define DHTPIN    14 // D5

DHT dht(DHTPIN, DHTTYPE, 12);
WiFiClient client;

float temperature, humidity;

const char* ssid="RIGON";
const char* password = "XXXXX";


//Colocar a API Key para escrita neste campo
//Ela é fornecida no canal que foi criado na aba API Keys
String apiKey = "XXXXX";
const char* server = "api.thingspeak.com";



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

   //Inicia um client TCP para o envio dos dados
  if (client.connect(server,80)) {
    String postStr = apiKey;
           postStr +="&amp;field1=";
           postStr += String(temperature);
           postStr +="&amp;field2=";
           postStr += String(humidity);
           postStr += "\r\n\r\n";

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
     Serial.print("Temperatura: ");
     Serial.print(temperature);
     Serial.print(" Umidade: ");
     Serial.println(humidity);
  }
  client.stop();

  delay(5000);

}
