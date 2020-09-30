#ifndef Lights_h
#define Lights_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Potentiometer.h"

class Lights
{
private:
    byte dataPin;
    byte pixelCount;

    float intensity;

    Adafruit_NeoPixel pixels;
    Potentiometer dimmer;

public:
    Lights(byte dataPin, byte pixelCount, byte dimmerPin) : dataPin(dataPin), pixelCount(pixelCount), dimmer(dimmerPin, 0, 1000, "Dimmer") {}
    ~Lights() {}

    void begin();
    void flash();
    void update();

    void updateFrame();
    void show();
};

#endif