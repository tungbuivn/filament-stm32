#include <Arduino.h>
#include "pwm_ctrl.h"
#include "tbt_thread.h"
#include "mylcd.h"
#include "pins.h"

PWMControl::PWMControl()
{

    this->trg = 0;
    this->start = 0;
    this->duty = 0;
    pinMode(PWM_BLDC, OUTPUT);
    pinMode(ONOFF, INPUT_PULLUP);
    // PWM_MAX_DUTY_CYCLE
    // decrease resolution to increase frequency
    // analogWriteResolution(PWM_RES);
    analogWriteFrequency(700);
    analogWrite(PWM_BLDC,0);
}

void PWMControl::execute()
{
//  analogWrite(PWM_BLDC, 95 * 255 / 100);
    TBT_THC(1,
        , ,
        // Serial.println("setup text"),
        this->trg = digitalRead(ONOFF),
        TBT_IF(this->trg == LOW,
            TBT_BLOCK(
                this->start = !this->start,
                if (this->start) {
                    this->duty = 99;
                } else {
                    this->duty = 0;
                },
                // this->tm=1,
                analogWrite(PWM_BLDC, (this->duty * 255) / 100),
                // Serial.println(duty),
                TBT_DELAY(500)
            ),

        ),
        //  analogWrite(PWM_BLDC,this->duty*255/100);

        // TBT_WAIT_THREAD(200, lcd)
    )
     
};