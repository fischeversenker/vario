#include <ESP8266WiFi.h>
#include <ezTime.h>
#include <limits.h>
#include "./Beeper.h"
#include "./Blinker.h"
#include "./Vario.h"

#ifndef WIFI_SSID
#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASSWORD "YOUR_PASSWORD"
#endif

#ifndef LONG_PRESS_INTVL
#define LONG_PRESS_INTVL 400
#endif

#ifndef LOG_INTVL
#define LOG_INTVL 100
#endif

const int startStopPin = D5; // 14

bool logging = false;

unsigned long buttonPressed = LONG_MAX;
unsigned long lastLogTime = 0;

bool isPressed = false;
// used to ignore presses after long press has been detected
// and button is continously being pressed
bool ignorePress = false;

Beeper beeper = Beeper();
Blinker blinker = Blinker();
Vario vario = Vario();

ICACHE_RAM_ATTR void startStopChangeCallback() {
  if (digitalRead(startStopPin) == LOW) {
    buttonPressed = millis();
    isPressed = true;
  } else {
    buttonPressed = LONG_MAX;
    isPressed = false;
    ignorePress = false;
  }
}

void toggle() {
  logging = !logging;
  if (logging) {
    beeper.confirmPositive();
  } else {
    beeper.confirmNegative();
  }
  blinker.blink();
}

bool isLongPress() {
  return isPressed && isLongEnoughInPast(buttonPressed, LONG_PRESS_INTVL);
}

void logData() {
  if (isLongEnoughInPast(lastLogTime, LOG_INTVL)) {
    int pitch = vario.getCurrentPitch();
    Serial.print(UTC.dateTime(ISO8601) + " vario: ");
    Serial.print(vario.getCurrentValue());
    Serial.print(", pitch: ");
    Serial.println(pitch);
    blinker.blink();

    beeper.beep(pitch, BEEPER_DEFAULT_DURATION, beepCooldown(pitch));

    lastLogTime = millis();
  }
}

// the higher the input the lower the duration
int beepCooldown(int beepPitch) {
  return (beepPitch * (-500.0 / 1024)) + 500;
}

bool isLongEnoughInPast(unsigned long when, int howLong) {
  return millis() - when > howLong;
}

void setup(){
  pinMode(startStopPin, INPUT_PULLUP);

  Serial.begin(115200);
  Serial.println();
  Serial.print("Booting");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  do {
    delay(500);
    Serial.print ( "." );
  } while ( WiFi.status() != WL_CONNECTED );

  Serial.println();
  Serial.println("Connected to WiFi");

 // wait for internet time
  waitForSync();
  Serial.println("Received internet time: " + UTC.dateTime());
  WiFi.mode(WIFI_OFF);

  attachInterrupt(digitalPinToInterrupt(startStopPin), startStopChangeCallback, CHANGE);

  beeper.confirmPositive();
}

void loop() {
  beeper.update();
  blinker.update();

  if (!ignorePress && isLongPress()) {
    ignorePress = true;
    toggle();
  }
  if (!logging) {
    return;
  }

  vario.update();

  logData();
  delay(10);
}
