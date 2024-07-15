#include <Arduino.h>
#include "pwm_ctrl.h"
#include "tbt_thread.h"
#include "mylcd.h"
#include "pins.h"
#include "events.h"
#include "buttons.h"

PWMControl *me=NULL;
PWMControl::PWMControl()
{

    me=this;
    this->trg = 0;
    this->start = 0;
    this->duty = 0;
    pinMode(PWM_BLDC, OUTPUT);
    // pinMode(ONOFF, INPUT_PULLUP);
    // PWM_MAX_DUTY_CYCLE
    // decrease resolution to increase frequency
    // analogWriteResolution(PWM_RES);
    analogWriteFrequency(700);
    analogWrite(PWM_BLDC, 0);
    /**
     * The on/off button can be trigger by hardware or software from lcd
     */
    eventSystem.addListener(EventType::BUTTON_TRIGGER,PWMControl::onOff);
    
}
bool PWMControl::onOff(EventData *dt) {
    if (!me) return false;
    auto ev=(ButtonState*)dt;
    if (ev->btn==BUTTON_STATE::BTN_FAN) {
        me->start = !me->start;
        if (me->start) {
            me->duty = 20;
        } else {
            me->duty = 0;
        };
        analogWrite(PWM_BLDC, (me->duty * 255) / 100);
        debug_printf("State %d, pwm: %d\n",me->start,me->duty);
    }
    return false;
   
}
void PWMControl::execute2(){

}
void PWMControl::execute()
{

    // static int btn=0;
    //  analogWrite(PWM_BLDC, 95 * 255 / 100);
    TBT_THC(1,
           
           
        
           
    )
};