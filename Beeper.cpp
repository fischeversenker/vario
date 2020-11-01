#include "./Beeper.h"
#include <queue>

unsigned long lastBeepStop = LONG_MAX;
unsigned long lastBeepStart = LONG_MAX;

boolean isBeeping = false;
boolean isPaused = false;

std::queue<struct Beep> pendingBeepsQueue;

Beeper::Beeper() {
  pinMode(BEEPER_PIN, OUTPUT);
  noTone(BEEPER_PIN);
}

void Beeper::beep() {
  beep(BEEPER_DEFAULT_PITCH);
}

void Beeper::beep(int pitch) {
  beep(pitch, BEEPER_DEFAULT_DURATION);
}

void Beeper::beep(int pitch, int duration) {
  pendingBeepsQueue.push(Beep(pitch, duration));
}

void Beeper::confirmPositive() {
  beep(880);
  beep(1660);
  beep(3320);
}

void Beeper::confirmNegative() {
  beep(1660);
  beep(440);
}

void Beeper::update() {
  if (isBeeping && millis() - lastBeepStart >= pendingBeepsQueue.front().duration) {
    noTone(BEEPER_PIN);
    isBeeping = false;
    lastBeepStop = millis();
    pendingBeepsQueue.pop();
  }

  if (_shouldBeep()) {
    _beep();
  }
}

// PRIVATE

void Beeper::_beep() {
  tone(BEEPER_PIN, pendingBeepsQueue.front().pitch);
  isBeeping = true;
  lastBeepStart = millis();
}

boolean Beeper::_shouldBeep() {
  boolean mayBeep = !isPaused && !isBeeping && millis() - lastBeepStop >= BEEPER_COOLDOWN;
  boolean hasBeeps = pendingBeepsQueue.size() > 0;
  return mayBeep && hasBeeps;
}
