# Wokwi Arduino Projekte

Dieses Repository enthält getrennte Arduino-Projekte für die Simulation mit Wokwi in Visual Studio Code.

## Projekte

- `blink/`: einfacher Blink-Sketch für Arduino Uno
- `sos/`: SOS-Sketch im Morsecode für Arduino Uno
- `esp32/`: ESP32-Blink-Sketch mit MQTT-Status für Home Assistant

Jeder Projektordner enthält eine eigene `.ino`-Datei, eine eigene `wokwi.toml` und eine eigene `diagram.json`. Dadurch kannst du den jeweiligen Unterordner auch einzeln als Wokwi-Projekt öffnen.

## ESP32 und MQTT

Der ESP32 verbindet sich mit deinem WLAN und sendet per MQTT an einen Broker im selben Netzwerk.

Vor dem Kompilieren brauchst du lokal eine Datei `esp32/secrets.h`. Kopiere dafür `esp32/secrets.example.h` und trage deine echten Daten ein:

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

## Kompilieren

Blink:

```powershell
arduino-cli compile --fqbn arduino:avr:uno --output-dir blink/build blink
```

SOS:

```powershell
arduino-cli compile --fqbn arduino:avr:uno --output-dir sos/build sos
```

ESP32:

```powershell
arduino-cli compile --fqbn esp32:esp32:esp32 --output-dir esp32/build esp32
```

Wokwi lädt die kompilierte Firmware aus dem jeweiligen `build/`-Ordner des Projekts.

## Automatisch bauen

In VS Code sind Build-Tasks eingerichtet:

- `Arduino: Build Blink for Wokwi`: kompiliert `blink/blink.ino`
- `Arduino: Build SOS for Wokwi`: kompiliert `sos/sos.ino`
- `Arduino: Build ESP32 for Wokwi`: kompiliert `esp32/esp32.ino`
- `Arduino: Watch and Build for Wokwi`: kompiliert `sos/sos.ino` automatisch neu, wenn sich die Datei ändert

Der Standard-Build-Task ist aktuell der SOS-Sketch und kann mit `Strg+Shift+B` gestartet werden.

## Voraussetzungen

- Visual Studio Code
- Wokwi-Erweiterung für VS Code
- Arduino CLI
- installierter Arduino-AVR-Core für `arduino:avr:uno`
- installierter ESP32-Core für `esp32:esp32:esp32`
- installierte Arduino-Library `PubSubClient`
