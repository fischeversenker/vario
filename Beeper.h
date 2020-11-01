/*
  Beeper.h - Beeper library
  Copyright (c) 2020 Felix Hamann.  All right reserved.
*/

// ensure this library description is only included once
#ifndef Beeper_h
#define Beeper_h

#include <Arduino.h>
#include <limits.h>

#ifndef BUZZER_PIN
#define BUZZER_PIN D4 //2
#endif

class Beeper
{
  public:
    Beeper();
    void beep(int);
    void update();

  private:
};

#endif
