#include "./Vario.h"

Vario::Vario()
{
  // manually initiate I2C Connection to control SDA and SCL pins
  Wire.begin(VARIO_SDA_PIN, VARIO_SCL_PIN);
}

void Vario::begin()
{
  if (!_bmp.begin())
  {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1)
      ;
  }

  _bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                   Adafruit_BMP280::SAMPLING_X1,     /* Temp. oversampling */
                   Adafruit_BMP280::SAMPLING_X4,     /* Pressure oversampling */
                   Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                   Adafruit_BMP280::STANDBY_MS_250); /* Standby time. */

  // init the last known altitude
  _addValue(getAltitude());
  delay(100);
  _addValue(getAltitude());
  _lastAltitude = _getWeightedAltitude();
}

void Vario::update()
{
  unsigned long now = millis();
  if (now - _lastUpdate >= VARIO_UPDATE_FREQUENCY)
  {
    _addValue(getAltitude());
    float currentAltitude = _getWeightedAltitude();
    _verticalSpeed = (currentAltitude - _lastAltitude) * (1000 / VARIO_UPDATE_FREQUENCY);
    _lastAltitude = currentAltitude;
    _lastUpdate = now;
  }
}

float Vario::getVerticalSpeed()
{
  return _verticalSpeed;
}

float Vario::getAltitude()
{
  return _bmp.readAltitude();
}

// PRIVATE

// calculates the weighted average of the last few altitude readings
float Vario::_getWeightedAltitude()
{
  float altitude = 0.0;
  float weightsSum = 0.0;
  int valueCount = _varioValues.size();
  for (int i = 0; i < valueCount; i++)
  {
    float weight = _getWeightForIndex(i, valueCount);
    altitude += weight * _varioValues[i];
    weightsSum += weight;
  }

  return (altitude / weightsSum);
}

// pushes curent value to the front of the vector and
// removes last value if vector is longer than VARIO_MAX_HISTORY_COUNT
void Vario::_addValue(float altitude)
{
  _varioValues.insert(_varioValues.begin(), altitude);
  if (_varioValues.size() > VARIO_MAX_HISTORY_COUNT)
  {
    _varioValues.pop_back();
  }
}

// weight for value at <index> in list of length <count>
inline float Vario::_getWeightForIndex(int index, int count)
{
  return 1 - sqrt(index * (1 / count));
}
