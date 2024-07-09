#pragma once
#include "tbt_thread.h"

class PWMControl : public BaseThread {
private:
    int trg;
    int start;
    int duty;
public:    
    PWMControl();
    void execute();
};