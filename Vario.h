/*
  Vario.h - Vario library
  Copyright (c) 2020 Felix Hamann.  All right reserved.
*/

// ensure this library description is only included once
#ifndef Vario_h
#define Vario_h

#include <Arduino.h>
#include <limits.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

#define SDA_PIN 0 // D3
#define SCL_PIN 2 // D4
#define MAX_VARIO_VALUES 300

class Vario
{
public:
  Vario();
  float getCurrentValue();
  void connect();
  void update();
  float getCurrentPitch();

private:
  void addValue();
  float getWeightForIndex(int index, int count);
};

#endif
