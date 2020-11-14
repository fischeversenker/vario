/*
  Beeper.h - Beeper library
  Copyright (c) 2020 Felix Hamann.  All right reserved.
*/

// ensure this library description is only included once
#ifndef Beeper_h
#define Beeper_h

#include <Arduino.h>
#include <limits.h>

#define BEEPER_PIN 14 //D5
#define BEEPER_DEFAULT_COOLDOWN 20
#define BEEPER_DEFAULT_PITCH 1660
#define BEEPER_DEFAULT_DURATION 70
#define BEEPER_MAX_PENDING 10

struct Beep
{
  int pitch;
  int duration;
  int cooldown;
  Beep(int pitch, int duration, int cooldown) : pitch(pitch), duration(duration), cooldown(cooldown) {}
};

class Beeper
{
public:
  Beeper();
  void beep(int pitch, int duration, int cooldown);
  void confirmPositive();
  void confirmNegative();
  void update();

private:
  void _beep();
  boolean _shouldBeep();
};

#endif
