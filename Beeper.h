/*
  Beeper.h - Beeper library
  Copyright (c) 2020 Felix Hamann.  All right reserved.
*/

// ensure this library description is only included once
#ifndef Beeper_h
#define Beeper_h

#include <Arduino.h>
#include <limits.h>

#define BEEPER_PIN 2 //D4
#define BEEPER_COOLDOWN 20
#define BEEPER_DEFAULT_PITCH 1660
#define BEEPER_DEFAULT_DURATION 70
#define BEEPER_MAX_PENDING 10

struct Beep {
  int pitch;
  int duration;
  Beep(int pitch, int duration): pitch(pitch), duration(duration) {}
};

class Beeper
{
  public:
    Beeper();
    void beep();
    void beep(int pitch);
    void beep(int pitch, int duration);
    void confirmPositive();
    void confirmNegative();
    void update();

  private:
    void _beep();
    boolean _shouldBeep();
};

#endif
