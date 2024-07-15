#include "buttons.h"

#define BUTTON_PRESS(button,evt) \
    TBT_IF_TRUE(digitalRead(button)==LOW, \
        TBT_WHILE(digitalRead(button)==LOW,), \
        state.btn=evt, \
        eventSystem.dispatchMessage(EventType::BUTTON_TRIGGER,&state) \
    )
Buttons::Buttons() {
    pinMode(PIN_BTN_ONOFF, INPUT_PULLUP);
    pinMode(PIN_BTN_SWING, INPUT_PULLUP);
    state.btn=BUTTON_STATE::BTN_NONE;
    
}

void Buttons::execute(){
    
    TBT_THC(1,
        BUTTON_PRESS(PIN_BTN_ONOFF,BUTTON_STATE::BTN_FAN),
        BUTTON_PRESS(PIN_BTN_SWING,BUTTON_STATE::BTN_SWING)
        
    )
};