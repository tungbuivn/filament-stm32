#pragma once

#include "tbt_thread.h"
#include "events.h"
#include "pins.h"
// #include <queue>
enum BUTTON_STATE {
    BTN_NONE,
    BTN_FAN,
    BTN_SWING
};

class ButtonState : public EventData {
public:
    BUTTON_STATE btn;
    // bool swingState;

};
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