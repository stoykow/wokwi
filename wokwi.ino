void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void blinkSignal(int duration) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(duration);
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
}

void loop() {
  // SOS im Morsecode: kurz kurz kurz, lang lang lang, kurz kurz kurz
  for (int i = 0; i < 3; i++) {
    blinkSignal(200);
  }


  for (int i = 0; i < 3; i++) {
    blinkSignal(600);
  }


  for (int i = 0; i < 3; i++) {
    blinkSignal(200);
  }

  delay(1400);
}
