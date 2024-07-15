#pragma once
#include "tbt_thread.h"
#include "events.h"

class PWMControl : public BaseThread {
private:
    int trg;
    int start;
    int duty;
    static bool onOff(EventData *);
public:    
    PWMControl();
    void execute();
    void execute2();
};