#include "buttons.h"
#include "pins.h"
#include "events.h"

Buttons::Buttons() {
    pinMode(ONOFF, INPUT_PULLUP);
    pinMode(SWING, INPUT_PULLUP);
    fan.isOn=false;
}
void Buttons::execute(){
    
    TBT_THC(1,
        TBT_IF_TRUE(digitalRead(ONOFF)==LOW,
            TBT_WHILE(digitalRead(ONOFF)==LOW,),
            fan.isOn=!fan.isOn,
            eventSystem.dispatchMessage(EventType::ONOFF_BUTTON,&fan),
        )
        // Serial.println("Begin blink led"),
    )
};