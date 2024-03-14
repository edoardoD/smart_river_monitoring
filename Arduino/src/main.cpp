#include <Arduino.h>
#include "kernel/Scheduler.h"
#include "Kernel/Task.h"

#define DEBUG 
Scheduler sched = Scheduler(50);

void setup() {
  
}

void loop() {
  sched.schedule();
}

