#pragma once
#include "tbt_thread.h"
// #include "eventData.h"
#include "events.h"

using namespace std;
class SwingControl;
extern SwingControl *swctrl;
class SwingControl : public BaseThread
{
    static bool __handler(EventData *dt) { return swctrl->handler(dt);}
    bool handler(EventData *dt);

public:
    SwingControl();
    void execute() override;
};