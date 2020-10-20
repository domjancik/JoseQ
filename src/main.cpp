#include <Arduino.h>

#include "settings.h"

#include "StepLED.h"
#include "Button.h"
#include "Potentiometer.h"
#include "Switches.h"

#include "arduino-timer.h"
auto timer = timer_create_default();

#include "Playback.h"
#include "Lights.h"
#include "Drumstick.h"

#define STEP_COUNT 16
#define STEP_PIN_START 38

#define LATCH_PIN 13
#define CLOCK_PIN 12
#define DATA_PIN_COUNT 12
byte dataPins[] = {22, 23, 24, 25, 26, 27, 30, 29, 28, 31, 32, 33};
Switches switches(dataPins, DATA_PIN_COUNT, LATCH_PIN, CLOCK_PIN);

StepLED stepLED(STEP_PIN_START, STEP_COUNT);

Button startButton(10, "Start");
Button stopButton(11, "Stop");

Playback playback(100);

Lights lights(9, 16, A7);

Potentiometer tempoPot(A0, MIN_TEMPO, MAX_TEMPO, "Tempo");

int step = 0;

long lastChange = 0;

// Drumsticks
#define ROW_CRASH 0
#define ROW_CBHIGH 1
#define ROW_CBLOW 2
#define ROW_BUCKET 3
#define ROW_SNARE 4
#define ROW_KICK 5

Drumstick drumCrash(2, A2, "crash");
Drumstick drumCBHigh(3, A3, "cbHigh");
Drumstick drumCBLow(4, A4, "cbLow");
Drumstick drumBucket(5, A5, "bucket");
Drumstick drumSnareLeft(6, A6, "snareLeft");
Drumstick drumSnareRight(7, A1, "snareRight");
Drumstick drumKick(8, A8, "kick");

void touch() {
  lastChange = millis();
}

// Callbacks
void startChanged(bool pressed)
{
  startButton.print();
  touch();

  if (pressed)
    playback.start();
}

void stopChanged(bool pressed)
{
  stopButton.print();
  touch();

  if (pressed)
    playback.stop();
}

void tempoChanged(int value)
{
  tempoPot.print();
  playback.setBPM(value);

  touch();
}

void stepChanged(int step)
{
  //step = (step + 1) % STEP_COUNT;
  stepLED.setLEDStep(step);

  if (switches.read()) {
    switches.print();
    touch();
  }

  if (!playback.isPlaying()) return;

  if (switches.get(step, ROW_CRASH)) drumCrash.play();
  if (switches.get(step, ROW_CBHIGH)) drumCBHigh.play();
  if (switches.get(step, ROW_CBLOW)) drumCBLow.play();
  if (switches.get(step, ROW_BUCKET)) drumBucket.play();
  if (switches.get(step, ROW_SNARE)) {
    if (step % 2 == 0) {
      drumSnareLeft.play();
    } else {
      drumSnareRight.play();
    }
  }

  if (switches.get(step, ROW_KICK))
  {
    lights.flash();
    drumKick.play();
  }
}

// Main code

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  stepLED.begin();

  switches.begin();

  startButton.init();
  stopButton.init();

  startButton.onChange(startChanged);
  stopButton.onChange(stopChanged);
  tempoPot.onChange(tempoChanged, 2);

  playback.setStepCallback(stepChanged);
  playback.stop();

  lights.begin();
}

void loop()
{
  startButton.update();
  stopButton.update();
  tempoPot.update();
  playback.update();
  lights.update();

  timer.tick();

  #ifdef TIMEOUT_ENABLED
  if (playback.isPlaying() && millis() - lastChange > TIMEOUT) {
    playback.stop();
    playback.stop();
  }
  #endif

  // delay(100);
}