#ifndef Potentiometer_h
#define Potentiometer_h

#include <Arduino.h>

class Potentiometer
{
private:
    uint8_t pin;
    int minValue;
    int maxValue;

    int lastValue;

    String name;

    void (*changeCallback)(int);
    int lastCallbackValue;
    int changeThreshold;
public:
    Potentiometer() {};
    Potentiometer(uint8_t pin, int minValue, int maxValue, String name) : pin(pin), minValue(minValue), maxValue(maxValue), name(name) {}
    ~Potentiometer() {}

    int getState();
    void onChange(void (*changeCallback)(int), int changeThreshold);

    void update();
    void print();
};

#endif