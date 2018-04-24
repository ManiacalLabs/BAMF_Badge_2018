#include "SimonButton.h"

SimonButton::SimonButton(byte btn, byte led, unsigned int tone, byte tone_pin) {
    _btn = btn;
    _led = led;
    _tone = tone;
    _tone_pin = tone_pin;
    pinMode(_led, OUTPUT);
    off();
    _btn_obj = Button(_btn, BTN_PULLUP, BTN_INVERT, BTN_DEBOUNCE);
}

void SimonButton::on(bool tone) {
    led_on(_led);
    if(tone){ _play_tone(); }
}

void SimonButton::off() {
    led_off(_led);
    noTone(TONE_PIN);
}

bool SimonButton::read() {
    return _btn_obj.read();
}

bool SimonButton::check() {
    if(_btn_obj.read()) {
        on();
        while(_btn_obj.read()){}
        off();
        return true;
    } else {
        off();
        return false;
    }
}

bool SimonButton::check_hold(long hold_time) {
    return _btn_obj.pressedFor(hold_time);
}

void SimonButton::_play_tone() {
    tone(TONE_PIN, _tone);
}