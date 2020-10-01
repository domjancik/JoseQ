#include "Lights.h"

#include <Adafruit_NeoPixel.h>
#include "arduino-timer.h"

extern Timer<> timer;

bool doUpdate(void *argument)
{
    ((Lights *)argument)->updateFrame();
    return true;
}

void Lights::begin()
{
    pixels = Adafruit_NeoPixel(pixelCount, dataPin, NEO_GRB + NEO_KHZ800);
    pixels.begin();
    pixels.clear();
    pixels.show(); // Send the updated pixel colors to the hardware.

    timer.every(16, doUpdate, this);
}

void Lights::flash()
{
    intensity = 1;
}

void Lights::update()
{
    dimmer.update();
}

void Lights::updateFrame()
{
    intensity = max(0, intensity - 0.1f);
    show();
}

void Lights::show()
{
    byte outIntensity = intensity * 255 * ((float)(dimmer.getState()) / 1000.0);
    byte eyeIntensity = 255.0f * ((float)(dimmer.getState()) / 1000.0);

    auto eyeColor = pixels.Color(eyeIntensity, 0, 0);
    auto heartColor = pixels.Color(0, outIntensity, 0);

    pixels.fill(heartColor, 0, 6);
    pixels.fill(eyeColor, 6, 2);

    pixels.show();
}
