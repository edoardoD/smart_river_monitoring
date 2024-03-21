#ifndef GATEWAY_H
#define GATEWAY_H

#include "config.h"
#include "devices/ServoMotor.h"
#include "devices/ButtonImpl.h"
#include "devices/ServoMotorImpl.h"
#include "devices/Lcd.h"

class Gateway
{
private:
    int gateDegree;
    bool automode;
    Lcd *lcd;
    ServoMotorImpl *servoMotor;
    ButtonImpl *button;
    SysTatus state;

public:
    SysTatus getState() const
    {
        return state;
    }

    void setState(SysTatus newState)
    {
        state = newState;
    }
    Gateway();

    /***
     * @brief do digital read on button pin
     */
    bool buttonRead();
    /***
     * @brief change mode from auto to manual and vice versa
     */
    void changeMode();
    /**
     * @brief create all device object
     * and initialize to auto mode to detect
     * degree of gate opening/closing
     ***/
    void init();
    /**
     * @brief set gate degree to open/close
     ***/
    void setGateDegree(int degree);

    /**
     * @brief get the current degree of the gate
     ***/
    int getGateDegree();

    /**
     * @brief get value of potentiometer
     ***/
    int getPotentioMeterValue();

    /**
     * @brief print the current state system on I2C LCD
     ***/
    void pritnState();

    ~Gateway();
};

#endif // GATEWAY_H