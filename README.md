# Wokwi Arduino Uno Projekt

Dieses Projekt enthält einen einfachen Arduino-Uno-Sketch für die Simulation mit Wokwi in Visual Studio Code.

## Dateien

- `wokwi.ino`: Arduino-Programm
- `diagram.json`: Schaltung für die Wokwi-Simulation
- `wokwi.toml`: Wokwi-Konfiguration mit den Pfaden zur kompilierten Firmware
- `build/`: kompilierte Dateien, die Wokwi lädt

## Programm

Der aktuelle Sketch lässt die eingebaute LED des Arduino Uno auf Pin 13 dreimal kurz blinken. Das entspricht dem Buchstaben `S` im Morsecode.

## Kompilieren

Wokwi für VS Code lädt nicht direkt die `.ino`-Datei, sondern die kompilierte Firmware aus dem Ordner `build/`. Nach Änderungen an `wokwi.ino` muss der Sketch deshalb neu kompiliert werden:

```powershell
arduino-cli compile --fqbn arduino:avr:uno --output-dir build .
```

Danach kann die Simulation in Wokwi neu gestartet werden.

## Automatisch bauen

In VS Code ist ein Build-Task eingerichtet:

- `Arduino: Build for Wokwi`: kompiliert einmalig
- `Arduino: Watch and Build for Wokwi`: kompiliert automatisch neu, wenn sich eine `.ino`-Datei ändert

Den normalen Build-Task kannst du mit `Strg+Shift+B` starten.

## Voraussetzungen

- Visual Studio Code
- Wokwi-Erweiterung für VS Code
- Arduino CLI
- installierter Arduino-AVR-Core für `arduino:avr:uno`
