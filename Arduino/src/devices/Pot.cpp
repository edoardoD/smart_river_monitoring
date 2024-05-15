#include "Pot.h"
#include "Arduino.h"

Potentiometer::Potentiometer(int pin){
  this->pin = pin;
} 
  
void Potentiometer::sync(){
  value = analogRead(pin);  
  updateSyncTime(millis());
}

/***
 * @brief get value of potentiometer and mapping it to 0-180 degree
 * with a step of 5 degree
 * @return value of potentiometer
 
*/
float Potentiometer::getValue(){

  value = map(value, 0, 1023, 0, 90) * 2;
  return value;
}

void Potentiometer::updateSyncTime(long time){
	lastTimeSync = time;
}

long Potentiometer::getLastSyncTime(){
	return lastTimeSync;
}
