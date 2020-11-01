#include <ESP8266WiFi.h>
#include <ezTime.h>
#include <limits.h>
#include "./Beeper.h"
#include "./Blinker.h"

#ifndef WIFI_SSID
#define WIFI_SSID "Plantopia"
#define WIFI_PASSWORD "genaudreizehn"
#endif

#ifndef LONG_PRESS_INTVL
#define LONG_PRESS_INTVL 400
#endif

#ifndef LOG_INTVL
#define LOG_INTVL 1000
#endif

const int startStopPin = D5; // 14
const int statusLedPin = D6; //12
const int pressurePin = A0; // 4

bool logging = false;

unsigned long buttonPressed = LONG_MAX;
unsigned long lastLogTime = 0;

bool isPressed = false;
// used to ignore presses after long press has been detected
// and button is continously being pressed
bool ignorePress = false;

Beeper beeper = Beeper();
Blinker blinker = Blinker();

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
    beeper.beep(1660);
  } else {
    beeper.beep(880);
  }
  blinker.blink();
}

bool isLongPress() {
  return isPressed && isLongEnoughInPast(buttonPressed, LONG_PRESS_INTVL);
}

int lastValue = 0;
int currentValue = 0;
void showDifference () {
  currentValue = analogRead(pressurePin);
  int difference = currentValue - lastValue;
  Serial.println(difference);

  if (difference > 10) {
    beeper.beep(1660 + difference * 4);
  } else if (difference < -20) {
    beeper.beep(800);
  }
  lastValue = currentValue;
}

void logData() {
  if (isLongEnoughInPast(lastLogTime, LOG_INTVL)) {
    Serial.println(UTC.dateTime(ISO8601) + ": ...");
    blinker.blink();
    lastLogTime = millis();
  }
}

bool isLongEnoughInPast(unsigned long when, int howLong) {
  return millis() - when > howLong;
}

void setup(){
  pinMode(startStopPin, INPUT_PULLUP);
  pinMode(statusLedPin, OUTPUT);

  digitalWrite(statusLedPin, LOW);

  Serial.begin(115200);
  Serial.println();
  Serial.print("Booting");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print ( "." );
  }
  Serial.println();
  Serial.println("Connected to WiFi");

 // wait for internet time
  waitForSync();
  Serial.println("Received internet time: " + UTC.dateTime());

  attachInterrupt(digitalPinToInterrupt(startStopPin), startStopChangeCallback, CHANGE);

  beeper.beep(1000);
  beeper.beep(1000);
}

void loop() {
  if (!ignorePress && isLongPress()) {
    ignorePress = true;
    toggle();
  }
  if (!logging) {
    return;
  }

  beeper.update();
  blinker.update();
  logData();
  showDifference();
  delay(100);
}
