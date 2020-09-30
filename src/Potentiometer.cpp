#include "Potentiometer.h"

#include <Arduino.h>

int Potentiometer::getState() 
{
    return lastValue;
}

void Potentiometer::onChange(void (*changeCallback)(int), int changeThreshold) 
{
    this->changeCallback = changeCallback;
    this->changeThreshold = changeThreshold;
}

void Potentiometer::update() 
{
    int newValue = map(analogRead(pin), 0, 1024, minValue, maxValue);
    
    if (changeCallback != nullptr && abs(newValue - lastCallbackValue) > changeThreshold) {
        changeCallback(newValue);
        lastCallbackValue = newValue;
    }

    lastValue = newValue;
}

void Potentiometer::print() 
{
    Serial.print(name);
    Serial.print(": ");
    Serial.println(getState());
}
