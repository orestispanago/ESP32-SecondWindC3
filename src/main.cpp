#include <Arduino.h>

int pin = 34;
unsigned long interval = 1000;
unsigned long previousMillis, currentMillis, pulseCount;
float windSpeed;

TaskHandle_t Task1;

void countPulses(void *parameter)
{
  for (;;)
  {
    if (analogRead(pin) != 0)
    {
      pulseCount++;
    }
    delay(20);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.print("setup() running on core ");
  Serial.println(xPortGetCoreID());
  xTaskCreatePinnedToCore(
      countPulses, /* Function to implement the task */
      "Task1",     /* Name of the task */
      10000,       /* Stack size in words */
      NULL,        /* Task input parameter */
      0,           /* Priority of the task */
      &Task1,      /* Task handle. */
      0);          /* Core where the task should run */
}

float calcWindSpeed()
{
  if (pulseCount != 0)
  {
    return 0.706 * ((pulseCount * 1000.0 / (currentMillis - previousMillis))) + 0.324;
  }
  return 0.0;
}

void loop()
{
  currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    Serial.print("pulseCount: \t");
    Serial.println(pulseCount);
    windSpeed = calcWindSpeed();
    previousMillis = currentMillis;
    pulseCount = 0;

    Serial.print("Wind speed: ");
    Serial.print(windSpeed);
    Serial.println(" m/s");
  }
}