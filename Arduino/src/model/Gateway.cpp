#include "Gateway.h"


Gateway::Gateway() {}

void Gateway::init()
{
    state = SysTatus::AUTO;
    button = new ButtonImpl(BUTTON_PIN);
    servoMotor = new ServoMotorImpl(GATE_PIN);
    pot = new Potentiometer(POT_PIN);
    lcd = new Lcd(0x27, 16, 2);
    servoMotor->on();
    servoMotor->setPosition(0);
}

String Gateway::enum_toString(SysTatus status)
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
    
    JsonDocument json;
    String jsonString;
    json["mode"] = enum_toString(state);

    // Serialize the JSON object to a string
    serializeJson(json, jsonString);
    MsgService.sendMsg(jsonString);
}

void Gateway::setGateDegree(int degree) {
    if(servoMotor->getPosition() != degree) {
        servoMotor->setPosition(degree);
    }
}


int Gateway::getPotentioMeterValue() {
    pot->sync();
    return pot->getValue();
}

void Gateway::pritnState() {

    int servoPosition = servoMotor->getPosition();
    int mappedPosition = map(servoPosition, 0, 180, 0, 100);
    String message = "Mode: " + this->enum_toString(this->state) + ", Gate percentage: " + String(mappedPosition);
    if (message != lastMessage) {
        lcd->clear();
        lcd->show(message);
        lastMessage = message;
    }
}

void Gateway::printMessage(String st1) {
    lcd->clear();
    lcd->show(st1);
}
