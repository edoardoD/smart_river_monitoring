  #include <Arduino.h>
#include "kernel/Scheduler.h"
#include "Kernel/Task.h"
#include "model/Gateway.h"
#include "task/ModeTask.h"
#include "task/WorkerTask.h"
  
  
#define DEBUG 
Scheduler sched = Scheduler(100);
Gateway gtw = Gateway();  

void setup() {
  gtw.init();
  ModeTask modeTask = ModeTask(&gtw, 100);
  sched.addTask(&modeTask);
  WorkerTask workerTask = WorkerTask(&gtw, 200);
  sched.addTask(&workerTask);
  Serial.begin(9600);
  Serial.println("Start");

}

void loop() {
  sched.schedule();
}

