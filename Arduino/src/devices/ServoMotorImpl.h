#ifndef _SERVO_MOTOR_IMPL_
#define _SERVO_MOTOR_IMPL_

#include "ServoMotor.h"
#include <Arduino.h>
#include "ServoTimer2.h"

class ServoMotorImpl: public ServoMotor{
    private:
        int pin;
        int degree;
        ServoTimer2 motor;

    public:
        ServoMotorImpl(int pin);

        void on() override;
        void off() override;
        void setPosition(int angle) override;
        int getPosition();
    
};

#endif