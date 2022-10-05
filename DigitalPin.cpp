#include <Arduino.h>
#include "DigitalPin.h"

//pin constrtuctor
DigitalPin::DigitalPin(int pin)
{
    pinMode(pin,OUTPUT);
    _pin = pin;
    //digitalWrite(5,LOW);
}

void DigitalPin::set_TCCRA()
{
    switch (_pin)
    {
    //timer 3 pins
    case 5:
        TCCR3A = 0;
        break;
    //timer 4
    case 6:
        TCCR4A = 0;
        break;
    //timer 5
    case 44:
        TCCR5A = 0;
        break;
    //timer 1
    case 11:
        TCCR1A = 0;
        break;
    default:
        break;
    }
}


void DigitalPin::set_TCCRB()
{
    switch (_pin)
    {
    //timer 3 pins
    case 5:
        TCCR3B = 0;
        TCCR3B |=(1<<WGM32); 
        TCCR3B |= (1<<CS32) |(0<<CS31) |(0<<CS30); 
        break;
    //timer 4
    case 6:
        TCCR4B = 0;
        TCCR4B |=(1<<WGM42); 
        TCCR4B |= (1<<CS42) |(0<<CS41) |(0<<CS40); 
        break;
    //timer 5
    case 44:
        TCCR5B = 0;
        TCCR5B |=(1<<WGM52); 
        TCCR5B |= (1<<CS52) |(0<<CS51) |(0<<CS50); 
        break;
    //timer 1
    case 11:
        TCCR1B = 0;
        TCCR1B |=(1<<WGM12); 
        TCCR1B |= (1<<CS12) |(0<<CS11) |(0<<CS10); 
        break;
    default:
        break;
    }

}

// Initializes counter to 0
void DigitalPin::set_TCNT()
{
    switch (_pin)
    {
    //timer 3 
    case 5:
        TCNT3 = 0;
        break;
    //timer 4
    case 6:
        TCNT4 = 0;
        break;
    //timer 5
    case 44:
        TCNT5 = 0;
        break;
    //timer 1
    case 11:
        TCNT1 = 0;
        break;
    default:
        break;
    }

}

//slow blinkrate
void DigitalPin::set_OCR_slow()
{
    switch (_pin)
    {
    //timer 3 pins
    case 5:
        OCR3A = 31250;
        break;
    //timer 4
    case 6:
        OCR4A = 31250;
        break;
    //timer 5
    case 44:
        OCR5A = 31250;
        break;
    //timer 1
    case 11:
        OCR1A = 31250;
        break;
    default:
        break;
    }

}

void DigitalPin::set_OCR_fast()
{
    switch (_pin)
    {
    //timer 3 pins
    case 5:
        OCR3A = 7812;
        break;
    //timer 4
    case 6:
        OCR4A = 7812;
        break;
    //timer 5
    case 44:
        OCR5A = 7812;
        break;
    //timer 1
    case 11:
        OCR1A = 7812;
        break;
    default:
        break;
    }

}

void DigitalPin::set_OCR_on()
{
    switch (_pin)
    {
    //timer 3 pins
    case 5:
        OCR3A = 0;
        break;
    //timer 4
    case 6:
        OCR4A = 0;
        break;
    //timer 5
    case 44:
        OCR5A = 0;
        break;
    //timer 1
    case 11:
        OCR1A = 0;
        break;
    default:
        break;
    }

}

void DigitalPin::set_TIMSK()
{
    switch (_pin)
    {
    //timer 3 pins
    case 5:
        TIMSK3 = 0;
        TIMSK3 |= (1<<OCIE3A);
        break;
    //timer 4
    case 6:
        TIMSK4 = 0;
        TIMSK4 |= (1<<OCIE4A);
        break;
    //timer 5
    case 44:
        TIMSK5 = 0;
        TIMSK5 |= (1<<OCIE5A);
        break;
    //timer 1
    case 11:
        TIMSK1 = 0;
        TIMSK1 |= (1<<OCIE1A);
        break;
    default:
        break;
    }
}