#pragma once
#include "tbt_thread.h"
class Temperature : public BaseThread {
private:
    int init;
    uint16_t rtd;
    uint8_t fault;
     float ratio;
     float temp;
public:    
    Temperature();
    void execute();
};