#include "ButtonImpl.h"

#include "Arduino.h"

ButtonImpl::ButtonImpl(int pin) : pin(pin){
    pinMode(pin, INPUT_PULLUP);
    
}

bool ButtonImpl::isPressed() {
    return digitalRead(pin);
}