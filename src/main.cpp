#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>
#include <DHTesp.h>

const byte dht_gpio = 4;
DHTesp dht;

AsyncWebServer server(80);
DNSServer dns;

void setup() {
  Serial.begin(115200);

  dht.setup(dht_gpio, DHTesp::DHT11);

  AsyncWiFiManager wifiManager(&server, &dns);

  Serial.println("Conectando al WiFi...");
  wifiManager.autoConnect("ESP32_Config");

  Serial.println("¡Conectado al WiFi con éxito!");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    TempAndHumidity data = dht.getTempAndHumidity();
    
    String html = "<h1>Monitor de Clima ESP32</h1>";
    
    if (dht.getStatus() == DHTesp::ERROR_NONE) {
      html += "<p>Temperatura: " + String(data.temperature) + " C</p>";
      html += "<p>Humedad: " + String(data.humidity) + " %</p>";
    } else {
      html += "<p>Error leyendo el sensor DHT11</p>";
    }
    
    request->send(200, "text/html", html);
  });

  server.begin();
}

void loop() {
  
}
