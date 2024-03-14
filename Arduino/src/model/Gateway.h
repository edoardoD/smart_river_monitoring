#ifndef GATEWAY_H
#define GATEWAY_H

#include "config.h"

class Gateway
{
private:
    int gateDegree;
    bool automode;
    bool isGateOpening();

public:
    Gateway();
    /**
     * @brief create all device object
     * and initialize to auto mode to detect 
     * degree of gate opening/closing 
     ***/
    void init();
    /**
     * @brief set gate degree to open/close
     ***/
    void setGateDegree(int degree);
    
    /**
     * @brief get the current degree of the gate
     ***/
    int getGateDegree();
    

    /**
     * @brief get the current degree of the gate
     ***/
    int getPotentioMeterValue();


    ~Gateway();
};

Gateway::Gateway(/* args */)
{
}

Gateway::~Gateway()
{
}

#endif // GATEWAY_H