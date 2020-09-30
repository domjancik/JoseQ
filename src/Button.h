#ifndef Button_h
#define Button_h

#include <Arduino.h>

class Button {
  private:
    byte pin;
    byte state;
    byte lastReading;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 50;
    String name;

    void (*changeCallback)(bool);
  public:
    Button(byte pin, String name) : name(name) {
      this->pin = pin;
      lastReading = LOW;
      changeCallback = nullptr;
      init();
    }
    void init() {
      pinMode(pin, INPUT_PULLUP);
      update();
    }

    void onChange(void (*changeCallback)(bool)) {
        this->changeCallback = changeCallback;
    }

    void update() {
      // You can handle the debounce of the button directly
      // in the class, so you don't have to think about it
      // elsewhere in your code
      byte newReading = digitalRead(pin);
      
      if (newReading != lastReading) {
        lastDebounceTime = millis();
      }
      if (millis() - lastDebounceTime > debounceDelay) {
        // Update the 'state' attribute only if debounce is checked
        if (changeCallback != nullptr && newReading != state) {
            changeCallback(newReading == LOW);
        }
        state = newReading;
      }
      lastReading = newReading;
    }
    byte getState() {
      return state;
    }
    bool isPressed() {
      return (getState() == LOW);
    }

    void print() {
        Serial.print(name);
        Serial.print(": ");
        Serial.println(isPressed());
    }
};

#endif