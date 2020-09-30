#ifndef Potentiometer_h
#define Potentiometer_h

#include <Arduino.h>

class Potentiometer
{
private:
    uint8_t pin;
    int minValue;
    int maxValue;
public:
    Potentiometer(uint8_t pin, int minValue, int maxValue) : pin(pin), minValue(minValue), maxValue(maxValue) {}
    ~Potentiometer() {}

    int getState();
};

#endif