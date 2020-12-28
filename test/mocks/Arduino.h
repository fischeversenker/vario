#ifndef TEST_MOCKS_ARDUINO_H
#define TEST_MOCKS_ARDUINO_H

#include <algorithm>

using PinNumber = int;

enum MockedPinModeType {
  OUTPUT,
  INPUT,
  INPUT_PULLUP,
};

void pinMode(PinNumber pin, MockedPinModeType type) {
  // just a stub yet.. extend to mock if needed
}

void noTone(PinNumber pin) {}
void tone(PinNumber pin, unsigned int frequency, unsigned long duration) {}
void tone(PinNumber pin, unsigned int frequency) {}

void delay(unsigned long delay) {}

template <class CompareableType>
CompareableType constrain(CompareableType v, CompareableType hi,
                          CompareableType lo) {
  return (v < lo) ? lo : (hi < v) ? hi : v;
  // C++17 -> return std::clamp<CompareableType>(x, a, b);
}

template <class MappedType>
constexpr MappedType map(MappedType value, MappedType fromLow,
                         MappedType fromHigh, MappedType toLow,
                         MappedType toHigh) {
  return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}

unsigned long millis() {
  //@todo use the system clock instead within testing framework.
  return 12345;
}

#endif // TEST_MOCKS_ARDUINO_H