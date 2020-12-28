#include <ESP8266WiFi.h>
#include <limits.h>
#include "Beeper.h"
#include <Blinker.h>
#include "Vario.h"

#ifndef WIFI_SSID
#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASSWORD "YOUR_PW"
#endif

#define LONG_PRESS_INTVL 400
#define LOG_INTVL 1000
#define START_STOP_PIN 5 // D1

boolean logging = false;
unsigned long lastLogTime = 0;

unsigned long buttonPressed = LONG_MAX;
boolean isPressed = false;
// used to ignore presses after long press has been detected
// and button is continously being pressed
boolean ignorePress = false;

Beeper beeper = Beeper();
Blinker blinker = Blinker();
Vario vario = Vario();

// interrupt callback for start/stop button presses/releases
ICACHE_RAM_ATTR void startStopChangeCallback()
{
  if (digitalRead(START_STOP_PIN) == LOW)
  {
    buttonPressed = millis();
    isPressed = true;
  }
  else
  {
    isPressed = false;
    ignorePress = false;
  }
}

void toggle()
{
  logging = !logging;
  if (logging)
  {
    beeper.confirmPositive();
    beeper.setMode(Beeper::MODE_VARIO);
  }
  else
  {
    beeper.confirmNegative();
    beeper.setMode(Beeper::MODE_NORMAL);
  }
}

void logData()
{
  Serial.print(F(" vertical speed: "));
  Serial.print(vario.getVerticalSpeed());
  Serial.print(F(" [m/s], altitude: "));
  Serial.print(vario.getAltitude());
  Serial.println(F(" [m]"));
  lastLogTime = millis();
  blinker.blink();
}

void setup()
{
  pinMode(START_STOP_PIN, INPUT_PULLUP);

  Serial.begin(115200);
  Serial.println();
  Serial.print(F("Booting"));

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  int wifiConnectionAttempts = 0;
  while (WiFi.status() != WL_CONNECTED && wifiConnectionAttempts <= 20)
  {
    wifiConnectionAttempts++;
    Serial.print(F("."));
    delay(500);
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println(F("Connected to WiFi"));
    beeper.confirmNegative();

  }
  // to save power switch off WIFI module
  WiFi.mode(WIFI_OFF);

  attachInterrupt(digitalPinToInterrupt(START_STOP_PIN), startStopChangeCallback, CHANGE);

  vario.begin();
  beeper.confirmNegative();
}

void loop()
{
  beeper.update();
  blinker.update();

  unsigned long now = millis();
  boolean isLongPress = isPressed && now - buttonPressed >= LONG_PRESS_INTVL;
  if (!ignorePress && isLongPress)
  {
    ignorePress = true;
    toggle();
  }

  // bail out if not currently logging
  if (!logging)
  {
    return;
  }

  vario.update();
  beeper.setVerticalSpeed(vario.getVerticalSpeed());

  if (now - lastLogTime >= LOG_INTVL)
  {
    logData();
  }
}
