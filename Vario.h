/*
  Vario.h
  Copyright (c) 2020 Felix Hamann.  All right reserved.
*/

#ifndef Vario_h
#define Vario_h

#include <vector>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
using namespace std;

#define VARIO_SDA_PIN 0 // D3
#define VARIO_SCL_PIN 2 // D4
#define VARIO_MAX_HISTORY_COUNT 10
#define VARIO_UPDATE_FREQUENCY 100

class Vario
{
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
  vector<float> _varioValues;

  Adafruit_BMP280 _bmp;
  unsigned long _lastUpdate = 0;
  float _lastAltitude = 0;
  float _verticalSpeed = 0;
};

#endif
