#include "Beeper.h"
#include <queue>

#ifdef PLATFORMIO_BUILD
#include <Arduino.h>
#else
#include "test/mocks/Arduino.h"
#endif

Beeper::Beeper()
{
  pinMode(BEEPER_PIN, OUTPUT);
  noTone(BEEPER_PIN);
}

void Beeper::setMode(beeper_mode mode)
{
  _mode = mode;
}

void Beeper::setVerticalSpeed(float vSpeed)
{
  _vSpeed = constrain(vSpeed, BEEPER_V_SPEED_MIN, BEEPER_V_SPEED_MAX);
}

void Beeper::confirmPositive()
{
  // C6 -> G6 -> C7
  tone(BEEPER_PIN, 523, BEEPER_DEFAULT_DURATION);
  delay(BEEPER_DEFAULT_DURATION * 1.4);
  tone(BEEPER_PIN, 784, BEEPER_DEFAULT_DURATION);
  delay(BEEPER_DEFAULT_DURATION * 1.4);
  tone(BEEPER_PIN, 1046, BEEPER_DEFAULT_DURATION);
}

void Beeper::confirmNegative()
{
  // G6 -> C6
  tone(BEEPER_PIN, 784, BEEPER_DEFAULT_DURATION);
  delay(BEEPER_DEFAULT_DURATION * 1.4);
  tone(BEEPER_PIN, 523, BEEPER_DEFAULT_DURATION);
}

void Beeper::update()
{
  if (_mode != MODE_VARIO)
  {
    return;
  }

  unsigned long now = millis();
  if (_isBeeping && now - _lastBeepStart >= BEEPER_DEFAULT_DURATION)
  {
    noTone(BEEPER_PIN);
    _isBeeping = false;
    _lastBeepStop = now;
  }

  if (!_isBeeping && now - _lastBeepStop >= _getPauseDuration())
  {
    _beep();
  }
}

// PRIVATE

void Beeper::_beep()
{
  tone(BEEPER_PIN, _getPitch());
  _isBeeping = true;
  _lastBeepStart = millis();
}

int Beeper::_getPauseDuration()
{
  if (_vSpeed > -0.2F && _vSpeed < 0.1F)
  {
    return LONG_MAX;
  }
  if (_vSpeed <= 0)
  {
    return map(_vSpeed, -2.F, 0.F, 3000.F, 0.F);
  }
  return map(_vSpeed, 0.F, 5.F, 1000.F, 70.F);
}

int Beeper::_getPitch()
{
  if (_vSpeed <= 0)
  {
    return map(_vSpeed, -2.F, 0.F, 50.F, 100.F);
  }
  return map(_vSpeed, 0.F, 5.F, 1000.F, 4000.F);
}
