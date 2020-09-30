#include <Arduino.h>

#include "StepLED.h"
#include "Button.h"
#include "Potentiometer.h"

#define STEP_COUNT 16
#define STEP_PIN_START 38

StepLED stepLED(STEP_PIN_START, STEP_COUNT);

Button startButton(10, "Start");
Button stopButton(11, "Stop");

Potentiometer tempoPot(A0, 96, 196, "Tempo");

int step = 0;

#define ROW_COUNT 16

bool row[ROW_COUNT];

int latchPin = 8;
int dataPin = 22;
int clockPin = 7;

#define DATA_PIN_START 22
#define DATA_PIN_COUNT 12
int dataPins[] = {22, 23, 24, 25, 26, 27, 30, 29, 28, 31, 32, 33};

#define BITS_PER_DATA_PIN 8
#define SWITCH_COUNT DATA_PIN_COUNT *BITS_PER_DATA_PIN

bool switchValues[SWITCH_COUNT];

byte switchVar1 = 72; //01001000

// Callbacks
void startChanged(bool pressed) {
  startButton.print();
}

void stopChanged(bool pressed) {
  stopButton.print();
}

void tempoChanged(int value) {
  tempoPot.print();
}

// Main code

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  stepLED.begin();

  startButton.init();
  stopButton.init();

  startButton.onChange(startChanged);
  stopButton.onChange(stopChanged);
  tempoPot.onChange(tempoChanged, 2);

  pinMode(latchPin, OUTPUT);

  pinMode(clockPin, OUTPUT);

  pinMode(dataPin, INPUT);

  for (size_t i = 0; i < SWITCH_COUNT; i++)
  {
    switchValues[i] = false;
  }

  for (size_t i = 0; i < DATA_PIN_COUNT; i++)
  {
    pinMode(dataPins[i], INPUT);
  }
}



void latchData(uint8_t latchPin)
{
  digitalWrite(latchPin, 1);
  delayMicroseconds(20);
  digitalWrite(latchPin, 0);
}

void shiftData(uint8_t clockPin)
{
  digitalWrite(clockPin, HIGH);
  digitalWrite(clockPin, LOW);
}

/**
 * Read switches into provided array
 * 
 * Returns true if changed 
 **/
bool readSwitches(int dataPins[], uint8_t dataPinsLength, uint8_t latchPin, uint8_t clockPin, bool switchValues[])
{
  latchData(latchPin);
  bool changed = false;

  for (int i = BITS_PER_DATA_PIN - 1; i >= 0; i--)
  {
    for (size_t dataPinIndex = 0; dataPinIndex < dataPinsLength; dataPinIndex++)
    {
      size_t switchIndex = i + (dataPinIndex * BITS_PER_DATA_PIN);
      bool lastValue = switchValues[switchIndex];
      bool newValue = digitalRead(dataPins[dataPinIndex]);
      switchValues[switchIndex] = newValue;

      changed = changed || lastValue != newValue;
    }
    shiftData(clockPin);
  }

  return changed;
}

void printSwitches(bool switchValues[])
{
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

void loop()
{
  if (readSwitches(dataPins, DATA_PIN_COUNT, latchPin, clockPin, switchValues))
    printSwitches(switchValues);

  step = (step + 1) % STEP_COUNT;
  stepLED.setLEDStep(step);

  startButton.update();
  stopButton.update();
  tempoPot.update();

  // delay(100);
}