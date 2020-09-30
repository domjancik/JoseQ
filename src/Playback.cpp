#include "Playback.h"

#include <Arduino.h>
#include "arduino-timer.h"

// auto timer = timer_create_default();
// Timer<3> timer;
extern Timer<> timer;


long bpmToStepMillis(int bpm)
{
    return 60000 / bpm;
}

void Playback::update()
{
}

bool timerFunction(void *argument)
{
    auto playbackInstance = ((Playback *)argument);
    playbackInstance->performStep();    
    return true;
}

void Playback::start()
{
    if (!playing) {
        playing = true;
        performStep();
    }
}

void Playback::stop() 
{
    if (!playing) {
        step = 0;
        if (stepCallback != nullptr) stepCallback(step);
    }
    playing = false;
}

void Playback::performStep()
{
    if (stepCallback != nullptr) stepCallback(step);
    
    step = (step + 1) % 16;

    if (isPlaying()) {
        armStep();
    }
}

void Playback::armStep() 
{
    timer.in(bpmToStepMillis(bpm), timerFunction, this);
}
