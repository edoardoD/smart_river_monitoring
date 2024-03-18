#ifndef __MODETASK__
#define __MODETASK__

#include "../kernel/TaskWithState.h"
#include "../model/Gateway.h"

enum class BtnState
{
  RELEASED,
  PRESSING
};  

class ModeTask : public TaskWithState<BtnState>
{

private:
  
  Gateway *gtw;
public:
  ModeTask(Gateway* gateway, int period);
  void tick();
    
};
#endif // __MODE_TASK__