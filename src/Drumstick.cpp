#include "Drumstick.h"

#include "arduino-timer.h"

extern Timer<> timer;

Drumstick::Drumstick(byte pin, byte calibrationPin, String name) : pin(pin),
                                                      calibrationPot(calibrationPin, MIN_DRUMSTICK_MILLIS, MAX_DRUMSTICK_MILLIS, "Drumstick Calibration"), name(name)
{
    begin();
}

void Drumstick::begin() 
{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

bool timerHandler(void * argument) {
    ((Drumstick*)argument)->stop();

    return false;
}

void Drumstick::play() 
{
    digitalWrite(pin, HIGH);
    calibrationPot.update();
    timer.in(calibrationPot.getState(), timerHandler, this);
}

void Drumstick::stop() 
{
    digitalWrite(pin, LOW);
}


