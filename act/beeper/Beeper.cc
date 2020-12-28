#include "Beeper.h"
#include <queue>

#ifdef PLATFORMIO_BUILD
#include <Arduino.h>
#else
#include "test/mocks/Arduino.h"
#endif

// @todo replace defines with constexpr to ensure typesafety
namespace {
  constexpr int kBeeperPin{14};
  constexpr int kDefaultCooldown{20};
  constexpr int kDefaultPitch{1660};
  constexpr int kDefaultDuration{70};
  constexpr int kMaxPending{10};
  constexpr float kMinVerticalSpeed{-5.0F};
  constexpr float kMaxVerticalSpeed{5.0F};
}

Beeper::Beeper()
    : mode_(Mode::kNormal), isBeeping_(false), lastBeepStop_(0),
      lastBeepStart_(0) {
  pinMode(kBeeperPin, OUTPUT);
  noTone(kBeeperPin);
}

void Beeper::setMode(Mode mode) { mode_ = mode; }

void Beeper::setVerticalSpeed(float vertical_speed) {
  verticalSpeed_ =
      constrain(vertical_speed, kMinVerticalSpeed, kMaxVerticalSpeed);
}

void Beeper::confirmPositive() {
  // C6 -> G6 -> C7
  tone(kBeeperPin, 523, kDefaultDuration);
  delay(kDefaultDuration * 1.4);
  tone(kBeeperPin, 784, kDefaultDuration);
  delay(kDefaultDuration * 1.4);
  tone(kBeeperPin, 1046, kDefaultDuration);
}

void Beeper::confirmNegative() {
  // G6 -> C6
  tone(kBeeperPin, 784, kDefaultDuration);
  delay(kDefaultDuration * 1.4);
  tone(kBeeperPin, 523, kDefaultDuration);
}

void Beeper::update() {
  if (mode_ != Mode::kVario) {
    return;
  }

  unsigned long now = millis();
  if (isBeeping_ && now - lastBeepStart_ >= kDefaultDuration) {
    noTone(kBeeperPin);
    isBeeping_ = false;
    lastBeepStop_ = now;
  }

  if (!isBeeping_ && now - lastBeepStop_ >= getPauseDuration()) {
    beep();
  }
}

void Beeper::beep() {
  tone(kBeeperPin, getPitch());
  isBeeping_ = true;
  lastBeepStart_ = millis();
}

int Beeper::getPauseDuration() const {
  if (verticalSpeed_ > -0.2F && verticalSpeed_ < 0.1F) {
    return std::numeric_limits<long>::max();
  }
  if (verticalSpeed_ <= 0) {
    return map(verticalSpeed_, -2.F, 0.F, 3000.F, 0.F);
  }
  return map(verticalSpeed_, 0.F, 5.F, 1000.F, 70.F);
}

int Beeper::getPitch() const {
  if (verticalSpeed_ <= 0) {
    return map(verticalSpeed_, -2.F, 0.F, 50.F, 100.F);
  }
  return map(verticalSpeed_, 0.F, 5.F, 1000.F, 4000.F);
}
