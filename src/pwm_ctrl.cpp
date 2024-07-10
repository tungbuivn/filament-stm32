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
    analogWrite(PWM_BLDC, 0);
}
void PWMControl::execute2(){

}
void PWMControl::execute()
{

    // static int btn=0;
    //  analogWrite(PWM_BLDC, 95 * 255 / 100);
    TBT_THC(1,
            , ,
            // Serial.println("setup text"),
            // btn = digitalRead(ONOFF),
            TBT_IF(digitalRead(ONOFF) == LOW,
                   TBT_BLOCK(
                        Serial.println("Start triggered"),
                       TBT_WHILE(digitalRead(ONOFF) == LOW, TBT_BLOCK()),
                        Serial.println("Start triggered released"),
                       this->start = !this->start,
                       if (this->start) {
                           this->duty = 50;
                       } else {
                           this->duty = 0;
                       },
                        analogWrite(BUZZER, 200); // Almost any value can be used except 0 and 255
// experiment to get the best tone
delay(500); // wait for a delayms ms
analogWrite(BUZZER, 0); // 0 turns it off
delay(300); // wait for a delayms ms
                       // this->tm=1,
                       analogWrite(PWM_BLDC, (this->duty * 255) / 100),
                       // Serial.println(duty),
                       // TBT_DELAY(500)
                       ),

                   ),
            //  analogWrite(PWM_BLDC,this->duty*255/100);

            // TBT_WAIT_THREAD(200, lcd)
    )
};