#ifndef __WORKERTASK__
#define __WORKERTASK__

#include "../kernel/Task.h"
#include "../model/Gateway.h"
#include <ArduinoJson.h>
#include "../kernel/MsgService.h"


class WorkerTask : public Task
{

private:
  Gateway *gtw;
  JsonDocument doc;
public:
  WorkerTask(Gateway* gateway, int period);
  void tick();
    
};
#endif // __MODE_TASK__