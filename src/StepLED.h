#ifndef StepLED_h
#define StepLED_h

class StepLED
{
private:
    int startPin;
    int pinCount;

    int getPin(int stepIndex);
    void clear();
public:
    StepLED(int _startPin, int _pinCount) : startPin(_startPin), pinCount(_pinCount) {}
    ~StepLED() {}

    void begin();
    void setLEDStep(int index);
};

#endif