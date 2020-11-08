#include "./Vario.h"
#include <vector>

int lastValue = 0;
int currentValue = 0;
Beeper internalBeeper;

std::vector<int> varioValues(MAX_VARIO_VALUES);

Vario::Vario(Beeper beeper) {
  pinMode(VARIO_PIN, INPUT);
  internalBeeper = beeper;
}

int Vario::getCurrentValue() {
  return analogRead(VARIO_PIN);
}

void Vario::update() {
  addValue();

  const int pitch = getCurrentPitch();
  if (abs(pitch) > 20) {
    int pitch = 1000 + (pitch * 4);
    internalBeeper.beep(pitch);
  }
}

// calcs the current pitch using a weighted window
int Vario::getCurrentPitch() {
  float pitch = 0.0;
  for (int i = 0; i < varioValues.size(); i++) {
    pitch += getWeightForIndex(i) * varioValues[i];
  }

  // TODO: work on this... probably produces very large wrong values
  return (int)pitch;
}

float Vario::getWeightForIndex(int index) {
  // index == 0 => 1
  // index == MAX_VARIO_VALUES => 0
  // TODO
  return 1 - (index * (1 / MAX_VARIO_VALUES));
}

// pushes curent value to the front of the deque and
// removes the last one if deque is longer than MAX_VARIO_VALUES
void Vario::addValue() {
  varioValues.insert(varioValues.begin(), getCurrentValue());
  if (varioValues.size() > MAX_VARIO_VALUES) {
    varioValues.pop_back();
  }
}
