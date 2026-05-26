# Wokwi Arduino Projekte

Dieses Repository enthält getrennte Arduino-Projekte für die Simulation mit Wokwi in Visual Studio Code.

## Projekte

- `blink/`: einfacher Blink-Sketch für Arduino Uno
- `sos/`: SOS-Sketch im Morsecode für Arduino Uno
- `esp32/`: ESP32-Blink-Sketch mit MQTT-Status für Home Assistant
- `esp32-webserver/`: ESP32-Webserver mit LED-Steuerung im Browser

Jeder Projektordner enthält eine eigene `.ino`-Datei, eine eigene `wokwi.toml` und eine eigene `diagram.json`. Dadurch kannst du den jeweiligen Unterordner auch einzeln als Wokwi-Projekt öffnen.

## WLAN in Wokwi

Für die Wokwi-Simulation muss das WLAN exakt so heißen:

```cpp
const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";
```

Auf echter ESP32-Hardware ersetzt du diese Werte in der jeweiligen lokalen `secrets.h` durch dein echtes WLAN.

## ESP32 und MQTT

Der ESP32 im Ordner `esp32/` verbindet sich mit deinem WLAN und sendet per MQTT an einen Broker im selben Netzwerk.

Vor dem Kompilieren brauchst du lokal eine Datei `esp32/secrets.h`. Kopiere dafür `esp32/secrets.example.h` und trage bei echter Hardware deine echten Daten ein:

```cpp
const char* WIFI_SSID = "DEIN_WLAN";
const char* WIFI_PASSWORD = "DEIN_WLAN_PASSWORT";

const char* MQTT_HOST = "192.168.1.10";
const int MQTT_PORT = 1883;
const char* MQTT_USER = "mqtt_user";
const char* MQTT_PASSWORD = "mqtt_passwort";
```

Die echte `secrets.h` wird von Git ignoriert.

Verwendete Topics:

- `home/esp32-wokwi/status`: `online` oder `offline`
- `home/esp32-wokwi/led`: `ON` oder `OFF`

## ESP32 Webserver

Der ESP32 im Ordner `esp32-webserver/` verbindet sich mit deinem WLAN und startet einen Webserver auf Port `80`. Im Browser kannst du dann die IP-Adresse des ESP32 öffnen und die eingebaute LED ein- oder ausschalten.

Vor dem Kompilieren brauchst du lokal eine Datei `esp32-webserver/secrets.h`. Kopiere dafür `esp32-webserver/secrets.example.h` und trage bei echter Hardware deine WLAN-Daten ein.

Die IP-Adresse wird nach dem WLAN-Verbindungsaufbau im seriellen Monitor ausgegeben.

Für Wokwi in VS Code ist `wokwigw` eingerichtet. Starte zuerst den Task:

```text
Wokwi: Start Gateway for ESP32 Webserver
```

Danach die Wokwi-Simulation starten und im Browser öffnen:

```text
http://localhost:8080
```

Der Task leitet `localhost:8080` auf Port `80` des simulierten ESP32 weiter.

## Kompilieren

Blink:

```powershell
arduino-cli compile --fqbn arduino:avr:uno --output-dir blink/build blink
```

SOS:

```powershell
arduino-cli compile --fqbn arduino:avr:uno --output-dir sos/build sos
```

ESP32 MQTT:

```powershell
arduino-cli compile --fqbn esp32:esp32:esp32 --output-dir esp32/build esp32
```

ESP32 Webserver:

```powershell
arduino-cli compile --fqbn esp32:esp32:esp32 --output-dir esp32-webserver/build esp32-webserver
```

Wokwi lädt die kompilierte Firmware aus dem jeweiligen `build/`-Ordner des Projekts.

## Automatisch bauen

In VS Code sind Build-Tasks eingerichtet:

- `Arduino: Build Blink for Wokwi`: kompiliert `blink/blink.ino`
- `Arduino: Build SOS for Wokwi`: kompiliert `sos/sos.ino`
- `Arduino: Build ESP32 for Wokwi`: kompiliert `esp32/esp32.ino`
- `Arduino: Build ESP32 Webserver for Wokwi`: kompiliert `esp32-webserver/esp32-webserver.ino`
- `Wokwi: Start Gateway for ESP32 Webserver`: startet `wokwigw` mit Port-Forwarding auf `localhost:8080`
- `Arduino: Watch and Build for Wokwi`: kompiliert `sos/sos.ino` automatisch neu, wenn sich die Datei ändert

Der Standard-Build-Task ist aktuell der SOS-Sketch und kann mit `Strg+Shift+B` gestartet werden.

## Voraussetzungen

- Visual Studio Code
- Wokwi-Erweiterung für VS Code
- Arduino CLI
- installierter Arduino-AVR-Core für `arduino:avr:uno`
- installierter ESP32-Core für `esp32:esp32:esp32`
- installierte Arduino-Library `PubSubClient` für das MQTT-Projekt
