#include <Arduino.h>
#include "kernel/Scheduler.h"
#include "Kernel/Task.h"

Scheduler sched;

void setup() {
  sched.init(50);
}

void loop() {
  sched.schedule();
}

