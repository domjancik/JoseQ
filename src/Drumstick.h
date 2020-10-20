#ifndef Drumstick_h
#define Drumstick_h

#include <Arduino.h>
#include "Potentiometer.h"

#define MAX_DRUMSTICK_MILLIS 200
#define MIN_DRUMSTICK_MILLIS 15

class Drumstick
{
private:
    byte pin;
    byte calibrationPin;

    Potentiometer calibrationPot;

    String name;
public:
    Drumstick(byte pin, byte calibrationPin, String name);
    ~Drumstick() {}

    void begin();

    void play();
    void stop();
};

#endif