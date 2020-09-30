#ifndef Potentiometer_h
#define Potentiometer_h

#include <Arduino.h>

class Potentiometer
{
private:
    uint8_t pin;
    int minValue;
    int maxValue;

    String name;
public:
    Potentiometer(uint8_t pin, int minValue, int maxValue, String name) : pin(pin), minValue(minValue), maxValue(maxValue), name(name) {}
    ~Potentiometer() {}

    int getState();

    void print();
};

#endif