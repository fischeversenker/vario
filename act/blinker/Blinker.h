/*
  Blinker.h
  Copyright (c) 2020 Felix Hamann.  All right reserved.
*/

#ifndef Blinker_h
#define Blinker_h

#define BLINKER_PIN 12 // D6
#define BLINKER_DURATION 150

class Blinker {
public:
  Blinker();
  void update();
  void blink();

private:
  unsigned long _lastBlinkStart = 0;
  bool _isOn = false;
};

#endif
