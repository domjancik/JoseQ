#ifndef Switches_h
#define Switches_h

#include <Arduino.h>

#define BITS_PER_DATA_PIN 8
#define DATA_PIN_COUNT 12
#define SWITCH_COUNT DATA_PIN_COUNT *BITS_PER_DATA_PIN
#define COLUMN_COUNT 16

class Switches
{
private:
    byte * dataPins;
    byte dataPinCount;
    byte latchPin;
    byte clockPin;

    bool switchValues[SWITCH_COUNT];

    void shiftData();
    void latchData();
public:
    Switches(byte dataPins[], byte dataPinCount, byte latchPin, byte clockPin) : dataPins(dataPins), dataPinCount(dataPinCount), latchPin(latchPin), clockPin(clockPin) {}
    ~Switches() {}

    void begin();

    bool read();
    void print();
    bool get(byte column, byte row);
};

#endif