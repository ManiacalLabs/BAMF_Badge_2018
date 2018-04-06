#ifndef SimonButton_h
#define SimonButton_h

#include <Arduino.h>
#include "Button.h"

#define led_on(pin) digitalWrite(pin, HIGH)
#define led_off(pin) digitalWrite(pin, LOW)

#define BTN_PULLUP true
#define BTN_INVERT true
#define BTN_DEBOUNCE 20

#define TONE_PIN 6

class SimonButton
{
  public:
    SimonButton(byte btn, byte led, unsigned int tone, byte tone_pin);
    bool read();
    bool check();
    bool check_hold(long hold_time);
    void on(bool tone);
    void on() { on(true); }
    void off();

  private:
    byte _btn;
    byte _led;
    unsigned _tone;
    byte _tone_pin;
    Button _btn_obj;

    void _play_tone();
};

#endif