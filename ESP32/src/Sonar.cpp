#include <Arduino.h>
#include "Sonar.h"

constexpr int tempAmb = 20; //default temperature in normal ambient

Sonar::Sonar(int echoPin, 
             int trigPin, 
             long maxTime) 
    : echoPin(echoPin), 
      trigPin(trigPin),
      temperature(tempAmb),
      timeOut(maxTime){
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

double Sonar::getSoundVelocity(){
    return 331.5 + 0.6*temperature;
}

double Sonar::getDistance(){
    digitalWrite(trigPin,LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin,LOW);

    double signal = (double)pulseIn(echoPin, HIGH);

    double time = signal / 1000.0 / 1000.0 / 2;
    double distance = time*getSoundVelocity();
    return distance;
}