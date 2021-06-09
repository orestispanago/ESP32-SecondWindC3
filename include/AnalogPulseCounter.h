#ifndef AnalogPulseCounter_h
#define AnalogPulseCounter_h
#include <Arduino.h>

TaskHandle_t Task1;
int pin = 34;
unsigned long pulseCount;

void pulseCounter(void *parameter)
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

void startPulseCounter()
{
    xTaskCreatePinnedToCore(
        pulseCounter, /* Function to implement the task */
        "Task1",     /* Name of the task */
        10000,       /* Stack size in words */
        NULL,        /* Task input parameter */
        0,           /* Priority of the task */
        &Task1,      /* Task handle. */
        0);          /* Core where the task should run */
}


#endif