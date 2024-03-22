
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

        if (MsgService.isMsgAvailable())
        {
            Msg *msg = MsgService.receiveMsg();
            deserializeJson(doc, msg->getContent());
            int valveValue = doc[String("value")];
            Serial.println(valveValue);
            gtw->setGateDegree(valveValue);
        }
        gtw->pritnState();
        break;
    case SysTatus::MANUAL:
        gtw->setGateDegree(gtw->getPotentioMeterValue());
        gtw->pritnState();
        break;
    default:
        break;
    }
}