#include <WebServer.h>
#include <WiFi.h>

#include "secrets.h"

const int ledPin = 2;
bool ledOn = false;
unsigned long lastIpPrint = 0;

WebServer server(80);

void setLed(bool state) {
  ledOn = state;
  digitalWrite(ledPin, ledOn ? HIGH : LOW);
}

String htmlPage() {
  String ledState = ledOn ? "an" : "aus";
  String buttonPath = ledOn ? "/off" : "/on";
  String buttonText = ledOn ? "LED ausschalten" : "LED einschalten";

  String page;
  page += "<!doctype html><html lang=\"de\"><head>";
  page += "<meta charset=\"utf-8\">";
  page += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  page += "<title>ESP32 Webserver</title>";
  page += "<style>";
  page += "body{font-family:system-ui,sans-serif;margin:2rem;max-width:40rem;line-height:1.5}";
  page += ".state{font-size:1.25rem;font-weight:700}";
  page += "a{display:inline-block;margin-top:1rem;padding:.75rem 1rem;background:#0b6bcb;color:white;text-decoration:none;border-radius:.4rem}";
  page += "</style></head><body>";
  page += "<h1>ESP32 Webserver</h1>";
  page += "<p>IP-Adresse: ";
  page += WiFi.localIP().toString();
  page += "</p><p>LED ist <span class=\"state\">";
  page += ledState;
  page += "</span>.</p><a href=\"";
  page += buttonPath;
  page += "\">";
  page += buttonText;
  page += "</a></body></html>";

  return page;
}

void handleRoot() {
  server.send(200, "text/html", htmlPage());
}

void handleOn() {
  setLed(true);
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleOff() {
  setLed(false);
  server.sendHeader("Location", "/");
  server.send(303);
}

void connectWiFi() {
  Serial.print("Verbinde mit WLAN ");
  Serial.print(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println();
  Serial.println("ESP32 Webserver startet");

  pinMode(ledPin, OUTPUT);
  setLed(false);

  connectWiFi();
  Serial.print("ESP32 Webserver erreichbar unter http://");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.begin();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  server.handleClient();

  if (millis() - lastIpPrint > 5000) {
    lastIpPrint = millis();
    Serial.print("Browser-URL: http://");
    Serial.println(WiFi.localIP());
  }
}
