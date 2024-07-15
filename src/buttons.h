#pragma once

#include "tbt_thread.h"
#include "events.h"
// #include <queue>

class OnOffState : public EventData {
public:
    bool isOn;
};
class Buttons : public BaseThread
{
private:
    OnOffState fan;
    // int queueLen;
public:
    Buttons();
    
    void execute() override;
};
// extern LedBlink *ledBlink;