/*
  Vario.h - Vario library
  Copyright (c) 2020 Felix Hamann.  All right reserved.
*/

// ensure this library description is only included once
#ifndef Vario_h
#define Vario_h

#include <Arduino.h>
#include <limits.h>

#define VARIO_PIN A0 //4
#define MAX_VARIO_VALUES 300

class Vario
{
  public:
    Vario();
    int getCurrentValue();
    void update();
    int getCurrentPitch();

  private:
    void addValue();
    float getWeightForIndex(int index, int count);

};

#endif
