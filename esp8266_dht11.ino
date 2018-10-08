#include <DHT.h>
#define DHTTYPE   DHT11
#define DHTPIN    14 // D5

DHT dht(DHTPIN, DHTTYPE, 12);

float temperature, humidity;

void setup() {
    Serial.begin(115200);
    delay(10);
    Serial.println();
    Serial.println("Inicializando placa");
    dht.begin();
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
