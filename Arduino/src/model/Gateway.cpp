#include "Gateway.h"


Gateway::Gateway() {}

void Gateway::init()
{
    state = SysTatus::AUTO;
    button = new ButtonImpl(BUTTON_PIN);
    servoMotor = new ServoMotorImpl(GATE_PIN);
    pot = new Potentiometer(POT_PIN);
    servoMotor->on();
    lcd = new Lcd(0x27, 16, 2);
    Serial.println("Gateway init");
}

String enum_toString(SysTatus status)
{
    switch (status)
    {
    case SysTatus::AUTO:
        return "AUTO";
    case SysTatus::MANUAL:
        return "MANUAL";
    default:
        return "UNKNOWN";
    }
}

bool Gateway::buttonRead(){
    return button->isPressed();
};

void Gateway::changeMode() {
    state= (state == SysTatus::AUTO) ? SysTatus::MANUAL : SysTatus::AUTO;
}

void Gateway::setGateDegree(int degree) {
    servoMotor->setPosition(degree);
}


int Gateway::getPotentioMeterValue() {
    return pot->getValue();
}

void Gateway::pritnState() {
    Serial.println(enum_toString(state));
    Serial.println("Gate degree: " + String(servoMotor->getPosition()));
}
