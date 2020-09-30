#ifndef Drumstick_h
#define Drumstick_h

#include <Arduino.h>
#include "Potentiometer.h"

#define MAX_DRUMSTICK_MILLIS 500
#define MIN_DRUMSTICK_MILLIS 50

class Drumstick
{
private:
    byte pin;
    byte calibrationPin;

    Potentiometer calibrationPot;
public:
    Drumstick(byte pin, byte calibrationPin);
    ~Drumstick() {}

    void begin();

    void play();
    void stop();
};

#endif