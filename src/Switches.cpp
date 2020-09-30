#include "Switches.h"

void Switches::shiftData()
{
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
}

void Switches::latchData()
{
    digitalWrite(latchPin, 1);
    delayMicroseconds(20);
    digitalWrite(latchPin, 0);
}

void Switches::begin()
{
    Serial.println("begin");
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);

    for (size_t i = 0; i < SWITCH_COUNT; i++)
    {
        switchValues[i] = false;
    }

    for (size_t i = 0; i < DATA_PIN_COUNT; i++)
    {
        pinMode(dataPins[i], INPUT);
    }
}

/**
 * Read switches into provided array
 * 
 * Returns true if changed 
 **/
bool Switches::read()
{
    Serial.println("printing");

    latchData();

    bool changed = false;

    for (int i = BITS_PER_DATA_PIN - 1; i >= 0; i--)
    {
        for (size_t dataPinIndex = 0; dataPinIndex < dataPinCount; dataPinIndex++)
        {
            size_t switchIndex = i + (dataPinIndex * BITS_PER_DATA_PIN);
            bool lastValue = switchValues[switchIndex];
            bool newValue = digitalRead(dataPins[dataPinIndex]);
            switchValues[switchIndex] = newValue;

            changed = changed || lastValue != newValue;
        }

        shiftData();
    }

    return changed;
}

void Switches::print()
{
    Serial.println("printing");

    for (size_t i = 0; i < SWITCH_COUNT; i++)
    {
        if (i % 16 == 0)
            Serial.println();
        if (i % 4 == 0)
            Serial.print(' ');
        Serial.print(switchValues[i]);
    }
    Serial.println();
    Serial.println();
    Serial.println("------");
}