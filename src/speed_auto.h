
/**
 * this class using to control fan speed depend on temperature
 */
#pragma once
#include "tbt_thread.h"
class SpeedAuto : public BaseThread {
public:   
    void execute() override; 
};