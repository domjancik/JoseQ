#include "StepLED.h"
#include <Arduino.h>

void StepLED::setLEDStep(int index)
{
    clear();
    digitalWrite(getPin(index), HIGH);
}

void StepLED::clear()
{
    for (int i = 0; i < pinCount; i++)
    {
        digitalWrite(getPin(i), LOW);
    }
}

void StepLED::begin()
{
    for (int i = 0; i < pinCount; i++)
    {
        pinMode(getPin(i), OUTPUT);
    }

    clear();
}

int StepLED::getPin(int stepIndex)
{
    return startPin + stepIndex;
}
