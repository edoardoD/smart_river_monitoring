#ifndef _SONAR_
#define _SONAR_

class Sonar {
    public:
        Sonar(int echoPin, int trigPin, long maxTime);
        double getDistance();

    private:
        double getSoundVelocity();
        int echoPin, trigPin;
        double temperature;
        long timeOut; //if the signal don't come back in time the object is too far away = no object detected
};

#endif