/*
  Beeper.h
  Copyright (c) 2020 Felix Hamann.  All right reserved.
*/

#ifndef Beeper_h
#define Beeper_h

#include <Arduino.h>
#include <limits.h>

#define BEEPER_PIN 14 //D5
#define BEEPER_DEFAULT_COOLDOWN 20
#define BEEPER_DEFAULT_PITCH 1660
#define BEEPER_DEFAULT_DURATION 70
#define BEEPER_MAX_PENDING 10
#define BEEPER_V_SPEED_MIN -5
#define BEEPER_V_SPEED_MAX 5

class Beeper
{
public:
  enum beeper_mode
  {
    MODE_NORMAL = 0,
    MODE_VARIO = 1,
  };

  Beeper();
  void update();
  void setMode(beeper_mode mode);
  void setVerticalSpeed(float vSpeed);
  void confirmPositive();
  void confirmNegative();

private:
  void _beep();
  int _getPauseDuration();
  int _getPitch();

  beeper_mode _mode = MODE_NORMAL;
  boolean _isBeeping = false;
  unsigned long _lastBeepStop = 0;
  unsigned long _lastBeepStart = 0;
  float _vSpeed = 0;
};

#endif
