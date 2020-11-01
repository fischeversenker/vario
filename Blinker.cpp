#include "./Blinker.h"

unsigned long lastBlinkStart = LONG_MAX;
boolean isOn = false;

Blinker::Blinker() {
  pinMode(BLINKER_PIN, OUTPUT);
  digitalWrite(BLINKER_PIN, HIGH);
}

void Blinker::blink() {
  digitalWrite(BLINKER_PIN, HIGH);
  isOn = true;
  lastBlinkStart = millis();
}

void Blinker::update() {
  if (isOn && millis() - lastBlinkStart >= BLINKER_DURATION) {
    digitalWrite(BLINKER_PIN, LOW);
    isOn = false;
  }
}
