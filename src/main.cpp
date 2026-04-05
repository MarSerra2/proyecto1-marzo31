#include <Arduino.h>
#include <DHTesp.h>

const byte led_gpio = 32;
const byte dht_gpio = 4;
DHTesp dht;

void estadoLed(bool estado) {
  digitalWrite(led_gpio, estado);
  delay(1000);
}

void setup() {
  Serial.begin(115200);
  pinMode(led_gpio, OUTPUT);
  dht.setup(dht_gpio, DHTesp::DHT11);
}
void loop() {
  TempAndHumidity data = dht.getTempAndHumidity();
  if (dht.getStatus() == DHTesp::ERROR_NONE) {
    Serial.print("Temperature: ");
    Serial.print(data.temperature);
    Serial.print("°C, Humidity: ");
    Serial.print(data.humidity);
    Serial.println("%");
  } else {
    Serial.println("Failed to read from DHT sensor!");
  }

  estadoLed(HIGH);
  estadoLed(LOW);
}
