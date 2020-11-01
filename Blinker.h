/*
  Blinker.h - Blinker library
  Copyright (c) 2020 Felix Hamann.  All right reserved.
*/

// ensure this library description is only included once
#ifndef Blinker_h
#define Blinker_h

#include <Arduino.h>
#include <limits.h>

#define BLINKER_PIN 12 //D6
#define BLINKER_DURATION 150

class Blinker
{
  public:
    Blinker();
    void blink();
    void update();

  private:
    unsigned long lastBlinkStart;
    boolean isOn;
};

#endif
