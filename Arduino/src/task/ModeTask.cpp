#include "ModeTask.h"
#include "Arduino.h"

ModeTask::ModeTask(Gateway *gateway, int period) : TaskWithState(period)
{
    gtw = gateway;
    setState(BtnState::RELEASED);
}

void ModeTask::tick()
{
    switch (this->getState())
    {
    case BtnState::RELEASED:
        Serial.println("RELEASED \n");
        if (!gtw->buttonRead())
        {
            setState(BtnState::PRESSING);
        }
        break;
    case BtnState::PRESSING:
        Serial.println("PRESSING \n");
        if (gtw->buttonRead())
        {
            gtw->changeMode();   
            setState(BtnState::RELEASED);
        }
        break;

    default:
        break;
    }
}