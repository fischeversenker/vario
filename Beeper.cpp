#include "./Beeper.h"

Beeper::Beeper() {
  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);
}

void Beeper::beep(int pitch) {
  tone(BUZZER_PIN, pitch, 150UL);
}

void Beeper::update() {

}
