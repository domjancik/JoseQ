#ifndef Playback_h
#define Playback_h

class Playback
{
private:
    int bpm;
    int step;

    bool playing;

    void (*stepCallback)(int);
    void armStep();

public:
    void performStep();
    Playback(int bpm) : bpm(bpm), playing(false) {}
    ~Playback() {}

    void setBPM(int bpm) { this->bpm = bpm; }
    void setStepCallback(void (*stepCallback)(int)) { this->stepCallback = stepCallback; }

    bool isPlaying() { return playing; }

    void start();
    void stop();
    void update();
};

#endif