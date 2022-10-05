#ifndef DigitalPin_h
#define DigitalPin_h
#include <Arduino.h>

class DigitalPin
{
    public:
    DigitalPin(int pin);
    void set_TCCRA();
    void set_TCCRB();
    void set_TCNT();
    void set_OCR_slow();
    void set_OCR_fast();
    void set_OCR_on();
    void set_TIMSK();
    private:
    int _pin;
};

#endif