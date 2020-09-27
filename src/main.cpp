#include <Arduino.h>

#define ROW_COUNT 16

bool row[ROW_COUNT];

int latchPin = 8;
int dataPin = 22;
int clockPin = 7;

#define DATA_PIN_START 22
#define DATA_PIN_COUNT 12
#define BITS_PER_DATA_PIN 8
#define SWITCH_COUNT DATA_PIN_COUNT *BITS_PER_DATA_PIN

bool switchValues[SWITCH_COUNT];

byte switchVar1 = 72; //01001000

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(latchPin, OUTPUT);

  pinMode(clockPin, OUTPUT);

  pinMode(dataPin, INPUT);

  for (size_t i = 0; i < SWITCH_COUNT; i++)
  {
    switchValues[i] = false;
  }

  for (size_t i = 0; i < DATA_PIN_COUNT; i++)
  {
    pinMode(DATA_PIN_START + i, INPUT);
  }
}

uint8_t shiftInCustom(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder)
{
  uint8_t value = 0;
  uint8_t i;

  for (i = 0; i < 8; ++i)
  {
    if (bitOrder == LSBFIRST)
      value |= digitalRead(dataPin) << i;
    else
      value |= digitalRead(dataPin) << (7 - i);
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
  }
  return value;
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
bool readSwitches(uint8_t dataPinFirst, uint8_t dataPinCount, uint8_t latchPin, uint8_t clockPin, bool switchValues[])
{
  latchData(latchPin);
  bool changed = false;

  for (int i = BITS_PER_DATA_PIN - 1; i >= 0; i--)
  {
    for (size_t dataPinIndex = 0; dataPinIndex < dataPinCount; dataPinIndex++)
    {
      size_t switchIndex = i + (dataPinIndex * BITS_PER_DATA_PIN);
      bool lastValue = switchValues[switchIndex];
      bool newValue = digitalRead(dataPinFirst + dataPinIndex);
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
    Serial.print(switchValues[i]);
  }
  Serial.println();
  Serial.println("------");
}

void loop()
{
  // put your main code here, to run repeatedly:

  /*switchVar1 = shiftInCustom(dataPin, clockPin, LSBFIRST);

  for (size_t i = 0; i < 8; i++)
  {
    Serial.print((switchVar1 << i & B10000000) == B10000000 ? 0 : 1);
  }
  Serial.println();*/

  if (readSwitches(DATA_PIN_START, DATA_PIN_COUNT, latchPin, clockPin, switchValues))
    printSwitches(switchValues);

  // Serial.println(switchVar1, BIN);
  // Serial.println(switchVar1);
  delay(100);
}