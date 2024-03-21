
#include "WorkerTask.h"

WorkerTask::WorkerTask(Gateway *gateway, int period) : Task(period)
{
    gtw = gateway;
}

void WorkerTask::tick()
{
    switch (gtw->getState())
    {
    case SysTatus::AUTO:

        gtw->pritnState();
        if (MsgService.isMsgAvailable())
        {
            Msg *msg = MsgService.receiveMsg();
            deserializeJson(doc, msg->getContent());
            int valveValue = doc[String("value")];
            Serial.println(valveValue);
            gtw->setGateDegree(valveValue);
        }
        break;
    case SysTatus::MANUAL:
        gtw->pritnState();
        gtw->setGateDegree(gtw->getPotentioMeterValue());
        break;
    default:
        break;
    }
}