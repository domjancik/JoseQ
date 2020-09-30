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
    auto color = pixels.Color(outIntensity, outIntensity, outIntensity);
    pixels.fill(color, 0, pixelCount);
    pixels.show();
}
