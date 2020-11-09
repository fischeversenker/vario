#include "./Beeper.h"
#include <queue>

unsigned long lastBeepStop = LONG_MAX;
unsigned long lastBeepStart = LONG_MAX;
unsigned long lastBeepCooldown = BEEPER_DEFAULT_COOLDOWN;

boolean isBeeping = false;

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
  beep(pitch, duration, BEEPER_DEFAULT_COOLDOWN);
}

void Beeper::beep(int pitch, int duration, int cooldown) {
  // optimize this...
  // only allow beeps while not beeping maybe?
  if (!isBeeping && pendingBeepsQueue.size() < BEEPER_MAX_PENDING) {
    pendingBeepsQueue.push(Beep(pitch, duration, cooldown));
  }
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
  lastBeepCooldown = pendingBeepsQueue.front().cooldown;
}

boolean Beeper::_shouldBeep() {
  boolean mayBeep = !isBeeping && millis() - lastBeepStop >= lastBeepCooldown;
  boolean hasBeeps = pendingBeepsQueue.size() > 0;
  return mayBeep && hasBeeps;
}
