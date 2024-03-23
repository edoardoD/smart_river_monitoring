#include "ModeTask.h"
#include "Arduino.h"
#include "model/logger.h"
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
        logger("Released");
        if (gtw->buttonRead())
        {
            setState(BtnState::PRESSING);
        }
        break;
    case BtnState::PRESSING:
        logger("Pressing");
        if (!gtw->buttonRead())
        {
            gtw->changeMode();   
            setState(BtnState::RELEASED);
        }
        break;

    default:
        break;
    }
}