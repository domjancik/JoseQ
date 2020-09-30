#include "Potentiometer.h"

#include <Arduino.h>

int Potentiometer::getState() 
{
    Serial.println(analogRead(pin));
    return map(analogRead(pin), 0, 1024, minValue, maxValue);
}

void Potentiometer::print() 
{
    Serial.print(name);
    Serial.print(": ");
    Serial.println(getState());
}
