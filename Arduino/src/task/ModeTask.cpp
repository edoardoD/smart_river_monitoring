#include "ModeTask.h"

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
        if (gtw->buttonRead())
        {
            setState(BtnState::PRESSING);
        }
        break;
    case BtnState::PRESSING:
        if (!gtw->buttonRead())
        {
            gtw->ChangeMode();   
            setState(BtnState::RELEASED);
        }
        break;

    default:
        break;
    }
}