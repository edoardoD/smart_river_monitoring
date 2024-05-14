#ifndef GATEWAY_H
#define GATEWAY_H

#include "config.h"
#include "devices/ServoMotor.h"
#include "devices/ButtonImpl.h"
#include "devices/ServoMotorImpl.h"
#include "devices/Lcd.h"
#include "devices/Pot.h"

class Gateway
{
private:
    bool automode;
    Lcd *lcd;
    ServoMotorImpl *servoMotor;
    ButtonImpl *button;
    SysTatus state;
    Potentiometer* pot;
    /***
     * @brief enum class to string of system status
     */
    String enum_toString(SysTatus status);

public:
    SysTatus getState() const
    {
        return state;
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
     * @brief set gate degree only if the current degree is different
     ***/
    void setGateDegree(int degree);

   
    /**
     * @brief get value of potentiometer
     ***/
    int getPotentioMeterValue();

    /**
     * @brief print the current state system on I2C LCD
     ***/
    void pritnState();

    void printMessage(String st1);
};

#endif // GATEWAY_H