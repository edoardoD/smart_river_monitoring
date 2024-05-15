
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
            String content = msg->getContent();
            //clean all the data before the first '{'
            int startPos = content.indexOf('{');
            if (startPos != -1)
            {
                content = content.substring(startPos);
            }
            DeserializationError err = deserializeJson(doc, content);
            if (err == DeserializationError::Ok)
            {
                int perc = doc["value"];
                int valveValue = map(perc, 0, 100, 0, 180);
                gtw->setGateDegree(valveValue);
            }
            else
            {
                gtw->printMessage(err.c_str());
            }
            //delete the msg
            delete msg;
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