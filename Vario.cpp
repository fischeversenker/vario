#include "./Vario.h"

int lastValue = 0;
int currentValue = 0;

Vario::Vario() {
  pinMode(VARIO_PIN, INPUT);
}

int Vario::value() {
  return analogRead(VARIO_PIN);
}

int Vario::difference () {
  currentValue = analogRead(VARIO_PIN);
  const int difference = currentValue - lastValue;
  lastValue = currentValue;

  return difference;
}
