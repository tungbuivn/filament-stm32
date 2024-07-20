#include <Arduino.h>
#include "swing_ctrl.h"
#include "events.h"
#include "tbt_thread.h"
#include "settings.h"
SwingControl::SwingControl()
{
    swctrl = this;
    eventSystem.addListener(EventType::SWING_UPDATED, SwingControl::__handler);
}
bool SwingControl::handler(EventData *dt)
{

    return false;
}
void SwingControl::execute()
{
    TBT_THC(5,
        TBT_IF_TRUE(settings->swing && settings->started && (settings->gear>0),

        )
    )
}
