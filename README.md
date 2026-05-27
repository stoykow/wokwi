# Wokwi Arduino Projekte

Dieses Repository enthält getrennte Arduino-Projekte für die Simulation mit Wokwi in Visual Studio Code.

## Projekt in VS Code öffnen

Du brauchst keinen eigenen GitHub- oder GitLab-Account, um dieses öffentliche Repository zu nutzen. Zum Herunterladen reicht Git über HTTPS.

Voraussetzungen:

- Visual Studio Code
- Git für Windows
- Wokwi-Erweiterung für Visual Studio Code
- Internetzugang für die Setup-Skripte

Repository klonen:

```powershell
cd C:\Users\DEIN_NAME\VSC
git clone https://github.com/stoykow/wokwi.git
cd wokwi
code .
```

Falls `code .` nicht funktioniert, öffne Visual Studio Code und wähle **File > Open Folder...**. Danach den Ordner `wokwi` auswählen.

Nach dem Öffnen in VS Code einmalig ausführen:

```powershell
.\scripts\setup-arduino.ps1
.\scripts\install-wokwigw.ps1
```

Alternativ kannst du in VS Code die Tasks starten:

- `Arduino: Setup CLI, Cores and Libraries`
- `Wokwi: Install Gateway`

Danach funktionieren die Build-Tasks ohne globale `arduino-cli`-Installation im `PATH`.

## Setup auf einem neuen Rechner

Die benötigten Programme werden projektlokal nach `.tools/` installiert. Dieser Ordner wird von Git ignoriert.

Arduino CLI, Board-Cores und Bibliotheken installieren:

```powershell
.\scripts\setup-arduino.ps1
```

Wokwi Gateway installieren:

```powershell
.\scripts\install-wokwigw.ps1
```

## Projekte

- `blink/`: einfacher Blink-Sketch für Arduino Uno
- `sos/`: SOS-Sketch im Morsecode für Arduino Uno
- `esp32/`: ESP32-Blink-Sketch mit MQTT-Status für Home Assistant
- `esp32-webserver/`: ESP32-Webserver mit LED-Steuerung im Browser

Jeder Projektordner enthält eine eigene `.ino`-Datei, eine eigene `wokwi.toml` und eine eigene `diagram.json`. Dadurch kannst du den jeweiligen Unterordner auch einzeln als Wokwi-Projekt öffnen.

## Wokwi Gateway

Für ESP32-Netzwerkprojekte wird `wokwigw` verwendet:

https://github.com/wokwi/wokwigw

Die ESP32-`wokwi.toml`-Dateien enthalten:

```toml
[net]
gateway = "ws://localhost:9011"
```

Starte vor der Simulation den VS-Code-Task:

```text
Wokwi: Start Gateway for ESP32 Webserver
```

Der Task startet `wokwigw` und leitet zusätzlich den simulierten ESP32-Webserver weiter:

```text
http://localhost:8080 -> 10.13.37.2:80
```

Danach kannst du den Webserver im Browser öffnen:

```text
http://localhost:8080
```

## WLAN in Wokwi

Für die Wokwi-Simulation muss das WLAN exakt so heißen:

```cpp
const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";
```

Auf echter ESP32-Hardware ersetzt du diese Werte in der jeweiligen lokalen `secrets.h` durch dein echtes WLAN.

## ESP32 und MQTT

Der ESP32 im Ordner `esp32/` verbindet sich mit WLAN und sendet per MQTT.

Mit `wokwigw` kann die Simulation Dienste auf deinem Rechner über diesen Host erreichen:

```cpp
const char* MQTT_HOST = "host.wokwi.internal";
const int MQTT_PORT = 1883;
```

Das funktioniert, wenn auf deinem Rechner ein MQTT-Broker auf Port `1883` läuft, zum Beispiel Mosquitto. Wenn dein Broker auf einem anderen Gerät im LAN läuft, kannst du stattdessen dessen IP-Adresse eintragen.

Für echte ESP32-Hardware trägst du in `esp32/secrets.h` dein echtes WLAN und die IP-Adresse deines MQTT-Brokers ein:

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

Der ESP32 im Ordner `esp32-webserver/` verbindet sich mit WLAN und startet einen Webserver auf Port `80`.

In Wokwi mit gestartetem Gateway öffnest du:

```text
http://localhost:8080
```

Auf echter Hardware öffnest du die IP-Adresse des ESP32 im Browser. Die IP-Adresse wird nach dem WLAN-Verbindungsaufbau im seriellen Monitor ausgegeben.

Vor dem Kompilieren brauchst du lokal eine Datei `esp32-webserver/secrets.h`. Kopiere dafür `esp32-webserver/secrets.example.h` und trage bei echter Hardware deine WLAN-Daten ein.

## Kompilieren

Blink:

```powershell
.\.tools\arduino-cli\arduino-cli.exe compile --fqbn arduino:avr:uno --output-dir blink/build blink
```

SOS:

```powershell
.\.tools\arduino-cli\arduino-cli.exe compile --fqbn arduino:avr:uno --output-dir sos/build sos
```

ESP32 MQTT:

```powershell
.\.tools\arduino-cli\arduino-cli.exe compile --fqbn esp32:esp32:esp32 --output-dir esp32/build esp32
```

ESP32 Webserver:

```powershell
.\.tools\arduino-cli\arduino-cli.exe compile --fqbn esp32:esp32:esp32 --output-dir esp32-webserver/build esp32-webserver
```

Wokwi lädt die kompilierte Firmware aus dem jeweiligen `build/`-Ordner des Projekts.

## Automatisch bauen

In VS Code sind Build-Tasks eingerichtet:

- `Arduino: Install CLI`: lädt `arduino-cli` nach `.tools/`
- `Arduino: Setup CLI, Cores and Libraries`: installiert `arduino-cli`, Board-Cores und `PubSubClient`
- `Arduino: Build Blink for Wokwi`: kompiliert `blink/blink.ino`
- `Arduino: Build SOS for Wokwi`: kompiliert `sos/sos.ino`
- `Arduino: Build ESP32 for Wokwi`: kompiliert `esp32/esp32.ino`
- `Arduino: Build ESP32 Webserver for Wokwi`: kompiliert `esp32-webserver/esp32-webserver.ino`
- `Wokwi: Install Gateway`: lädt `wokwigw` nach `.tools/`
- `Wokwi: Start Gateway for ESP32 Webserver`: startet `wokwigw` mit Port-Forwarding auf `localhost:8080`
- `Arduino: Watch and Build for Wokwi`: kompiliert `sos/sos.ino` automatisch neu, wenn sich die Datei ändert

Der Standard-Build-Task ist aktuell der SOS-Sketch und kann mit `Strg+Shift+B` gestartet werden.
