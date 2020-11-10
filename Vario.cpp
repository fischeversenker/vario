#include "./Vario.h"
#include <vector>

int lastValue = 0;
int currentValue = 0;

std::vector<int> varioValues(MAX_VARIO_VALUES);

Vario::Vario()
{
  pinMode(VARIO_PIN, INPUT);
}

int Vario::getCurrentValue()
{
  return analogRead(VARIO_PIN);
}

void Vario::update()
{
  addValue();
}

// calcs the current pitch using a weighted window
int Vario::getCurrentPitch()
{
  float pitch = 0.0;
  float weightsSum = 0.0;
  int valueCount = varioValues.size();
  for (int i = 0; i < valueCount; i++)
  {
    float weight = getWeightForIndex(i, valueCount);
    pitch += weight * varioValues[i];
    weightsSum += weight;
  }

  return (int)(pitch / weightsSum);
}

// PRIVATE

// pushes curent value to the front of the deque and
// removes the last one if vector is longer than MAX_VARIO_VALUES
void Vario::addValue()
{
  varioValues.insert(varioValues.begin(), getCurrentValue());
  if (varioValues.size() > MAX_VARIO_VALUES)
  {
    varioValues.pop_back();
  }
}

// weight for value at <index> in list of length <count>
float Vario::getWeightForIndex(int index, int count)
{
  return 1 - sqrt(index * (1 / count));
}
