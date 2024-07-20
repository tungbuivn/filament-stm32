#pragma once

#include "tbt_thread.h"
#include "events.h"
#include "pins.h"
#include "eventData.h"
// #include <queue>


class Buttons : public BaseThread
{
private:
    ButtonState state;
    // int queueLen;
public:
    Buttons();
    
    void execute() override;
};

// extern LedBlink *ledBlink;