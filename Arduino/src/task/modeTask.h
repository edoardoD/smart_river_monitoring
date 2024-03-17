#ifndef __MODETASK__
#define __MODETASK__

#include "../kernel/Task.h"

class ModeTask : public Task
{
public:
  ModeTask(int period) : Task(period)
  {
  }

  void tick()
  {
    // Serial.println("ModeTask");
  }
  private: 
};



#endif // __MODE_TASK__