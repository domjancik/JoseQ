#include <Arduino.h>

#define ROW_COUNT 16

bool row[ROW_COUNT];

int latchPin = 8;
int dataPin = 9;
int clockPin = 7;

byte switchVar1 = 72; //01001000

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(latchPin, OUTPUT);

  pinMode(clockPin, OUTPUT);

  pinMode(dataPin, INPUT);
}

uint8_t shiftInCustom(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder) {
	uint8_t value = 0;
	uint8_t i;

	for (i = 0; i < 8; ++i) {
		if (bitOrder == LSBFIRST)
			value |= digitalRead(dataPin) << i;
		else
			value |= digitalRead(dataPin) << (7 - i);
		digitalWrite(clockPin, HIGH);
		digitalWrite(clockPin, LOW);
	}
	return value;
}

void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(latchPin, 1);
  delayMicroseconds(20);
  digitalWrite(latchPin, 0);
  switchVar1 = shiftInCustom(dataPin, clockPin, LSBFIRST);

  for (size_t i = 0; i < 8; i++)
  {
    Serial.print((switchVar1 << i & B10000000) == B10000000 ? 0 : 1);
  }
  Serial.println();
  
  // Serial.println(switchVar1, BIN);
  // Serial.println(switchVar1);
  delay(100);
}