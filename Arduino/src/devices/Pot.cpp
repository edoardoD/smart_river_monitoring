#include "Pot.h"
#include "Arduino.h"

Potentiometer::Potentiometer(int pin){
  this->pin = pin;
} 
  
void Potentiometer::sync(){
  value = analogRead(pin);  
  updateSyncTime(millis());
}

float Potentiometer::getValue(){
  
  value = map(value, 0, 1023, 0, 180);
  return value;
}

void Potentiometer::updateSyncTime(long time){
	lastTimeSync = time;
}

long Potentiometer::getLastSyncTime(){
	return lastTimeSync;
}
