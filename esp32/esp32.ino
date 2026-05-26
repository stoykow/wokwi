#include <PubSubClient.h>
#include <WiFi.h>

#include "secrets.h"

const int ledPin = 2;
const char* deviceId = "esp32-wokwi";
const char* statusTopic = "home/esp32-wokwi/status";
const char* ledTopic = "home/esp32-wokwi/led";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void connectMqtt() {
  while (!mqttClient.connected()) {
    if (mqttClient.connect(deviceId, MQTT_USER, MQTT_PASSWORD, statusTopic, 0, true, "offline")) {
      mqttClient.publish(statusTopic, "online", true);
    } else {
      delay(2000);
    }
  }
}

void publishLedState(bool isOn) {
  mqttClient.publish(ledTopic, isOn ? "ON" : "OFF", true);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  connectWiFi();
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  connectMqtt();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  if (!mqttClient.connected()) {
    connectMqtt();
  }

  mqttClient.loop();

  digitalWrite(ledPin, HIGH);
  publishLedState(true);
  delay(500);

  mqttClient.loop();

  digitalWrite(ledPin, LOW);
  publishLedState(false);
  delay(500);
}
