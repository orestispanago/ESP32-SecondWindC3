#include <Arduino.h>
#include "AnalogPulseCounter.h"

unsigned long interval = 1000;
unsigned long previousMillis, currentMillis, elapsedT;
float windSpeed;

void setup()
{
  Serial.begin(115200);
  startPulseCounter(); // Runs on second core
}

float calcWindSpeed(unsigned long pulses, unsigned long elapsedT)
{
  if (pulses != 0)
  {
    return 0.706 * ((pulses * 1000.0 / (elapsedT))) + 0.324;
  }
  return 0.0;
}

void loop()
{
  currentMillis = millis();
  elapsedT = currentMillis - previousMillis;
  if (elapsedT >= interval)
  {
    Serial.print("pulseCount: \t");
    Serial.println(pulseCount);
    windSpeed = calcWindSpeed(pulseCount, elapsedT);
    previousMillis = currentMillis;
    pulseCount = 0;

    Serial.print("Wind speed: ");
    Serial.print(windSpeed);
    Serial.println(" m/s");
  }
}