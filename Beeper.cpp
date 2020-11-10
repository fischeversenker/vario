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

void Beeper::beep(int pitch = BEEPER_DEFAULT_PITCH, int duration = BEEPER_DEFAULT_DURATION, int cooldown = BEEPER_DEFAULT_COOLDOWN) {
  // optimize this...
  // only allow beeps while not beeping maybe?
  if (pendingBeepsQueue.size() < BEEPER_MAX_PENDING) {
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
