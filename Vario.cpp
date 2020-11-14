#include "./Vario.h"
#include <vector>

int lastValue = 0;
int currentValue = 0;

std::vector<int> varioValues(MAX_VARIO_VALUES);
Adafruit_BMP280 bmp; // I2C

Vario::Vario()
{
  // manually initiate I2C Connection to control SDA and SCL pins
  Wire.begin(SDA_PIN, SCL_PIN);
}

float Vario::getCurrentValue()
{
  return bmp.readPressure();
}

void Vario::connect()
{
  while(!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    delay(500);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void Vario::update()
{
  addValue();
}

float Vario::getCurrentPitch()
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

  return (pitch / weightsSum);
}

// PRIVATE

// pushes curent value to the front of the vector and
// removes last value if vector is longer than MAX_VARIO_VALUES
void Vario::addValue()
{
  varioValues.insert(varioValues.begin(), getCurrentValue());
  if (varioValues.size() > MAX_VARIO_VALUES)
  {
    varioValues.pop_back();
  }
}

// weight for value at <index> in list of length <count>
inline float Vario::getWeightForIndex(int index, int count)
{
  return 1 - sqrt(index * (1 / count));
}
