#include "./Blinker.h"

Blinker::Blinker()
{
  pinMode(BLINKER_PIN, OUTPUT);
  digitalWrite(BLINKER_PIN, HIGH);
}

void Blinker::blink()
{
  digitalWrite(BLINKER_PIN, HIGH);
  _isOn = true;
  _lastBlinkStart = millis();
}

void Blinker::update()
{
  if (_isOn && millis() - _lastBlinkStart >= BLINKER_DURATION)
  {
    digitalWrite(BLINKER_PIN, LOW);
    _isOn = false;
  }
}
