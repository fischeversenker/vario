/*
  Beeper.h
  Copyright (c) 2020 Felix Hamann.  All right reserved.
*/

#ifndef ACT_BEEPER_BEEPER_H
#define ACT_BEEPER_BEEPER_H

class Beeper {
public:
  enum class Mode { kNormal = 0, kVario };

  Beeper();
  void update();
  void setMode(Mode mode);
  void setVerticalSpeed(float vertical_speed);
  void confirmPositive();
  void confirmNegative();

private:
  void beep();
  int getPauseDuration() const;
  int getPitch() const;

  Mode mode_;
  bool isBeeping_;
  unsigned long lastBeepStop_;
  unsigned long lastBeepStart_;
  float verticalSpeed_;
};

#endif // ACT_BEEPER_BEEPER_H
