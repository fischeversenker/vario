/*
  Vario.h
  Copyright (c) 2020 Felix Hamann.  All right reserved.
*/

#ifndef SENSE_VARIO_VARIO_H
#define SENSE_VARIO_VARIO_H

#include <Adafruit_BMP280.h>

#include <vector>

#define VARIO_SDA_PIN 0 // D3
#define VARIO_SCL_PIN 2 // D4
#define VARIO_MAX_HISTORY_COUNT 10
#define VARIO_UPDATE_FREQUENCY 100

class Vario {
public:
  Vario();
  void begin();
  void update();
  float getAltitude();
  float getVerticalSpeed();

private:
  void _addValue(float value);
  float _getWeightedAltitude();
  float _getWeightForIndex(int index, int count);
  std::vector<float> _varioValues;

  Adafruit_BMP280 _bmp;
  unsigned long _lastUpdate = 0;
  float _lastAltitude = 0;
  float _verticalSpeed = 0;
};

#endif // SENSE_VARIO_VARIO_H
