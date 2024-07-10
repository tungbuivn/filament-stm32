#pragma once
#include "tbt_thread.h"
#include <Adafruit_MAX31865.h>
class Temperature : public BaseThread {
private:
    int init;
    uint16_t rtd;
    uint8_t fault;
    float ratio;
    float temp;
    uint32_t tm1;
    uint32_t tm2;
    uint32_t tm3;
    uint32_t tm4;
    // TemperatureContext *thermoContext;
public:    
    Temperature();
    void execute();
};