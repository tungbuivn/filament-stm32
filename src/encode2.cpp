
// #pragma once
#include "encode2.h"
#include <Arduino.h>
#include "tbt_thread.h"
#include <vector>
#include <functional>
#include "pins.h"
#include "events.h"

// #include <Encoder.h>

static  int lastA=HIGH;
static  int lastB=HIGH;
static EncoderRotate* rotaryEncoder=NULL;


   
void EncoderClick::execute() {
    static int state=0;
    static int i=0;

    
    state=digitalRead(PIN_ENCODER_CLICK);

    
    TBT_THC(5,,
        TBT_IF_TRUE(state==HIGH,
            TBT_BLOCK(
                // wait user release button
                TBT_WHILE(digitalRead(PIN_ENCODER_CLICK)==HIGH,),
                eventSystem.dispatchMessage(EventType::ENCODER_CLICK,NULL),
            )
        )
    )
}

EncoderRotate::EncoderRotate(): BaseThread(){ 
    rotaryEncoder=this;
    currentA=lastA;
    currentB=lastB;
    phase = lblLoop;

    pinMode(PIN_ENCODER_A,INPUT);
    pinMode(PIN_ENCODER_B,INPUT);
    pinMode(PIN_ENCODER_CLICK,INPUT);
   
    currentA=digitalRead(PIN_ENCODER_A);
    currentB=digitalRead(PIN_ENCODER_B);

    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_A), EncoderRotate::triggerA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_B), EncoderRotate::triggerB, CHANGE);

}

#define cond(x, y, p, ...)      \
    if ((ra == x) && (rb == y)) \
    {                           \
        phase = p;              \
        __VA_ARGS__;            \
    }

bool EncoderRotate::countRotate(int ra,int rb)
{
    bool done=false;
    EncoderData evt;
    // readData;
    switch (phase)
    {
   
        case lblLoop: // HIGH_HIGH
            // trigger press ?
            // CW ?
            cond(LOW, HIGH, lblCW) else cond(HIGH, LOW, lblCCW);
            break;
        case lblCW: // LOW_HIGH
            cond(LOW, LOW, lblCW1) else cond(HIGH, HIGH, lblLoop);
            break;
        case lblCW1: // LOW_LOW
            cond(HIGH, LOW, lblCW2) else cond(LOW, HIGH, lblCW);
            break;
        case lblCW2: // HIGH_LOW
            cond(HIGH, HIGH, lblLoop,  
                evt.dir=ENCODER_DIRECTION::RIGHT;
                eventSystem.dispatchMessage(EventType::ENCODER_ROTATE,&evt);
                done= true;
            ) else cond(LOW, LOW, lblCW1);
            break;
        // CCW ?
        case lblCCW: // HIGH_LOW
            cond(LOW, LOW, lblCCW1) else cond(HIGH, HIGH, lblLoop);
            break;
        case lblCCW1: // LOW_LOW
            cond(LOW, HIGH, lblCCW2) else cond(HIGH, LOW, lblCCW);
            break;
        case lblCCW2: // LOW_HIGH
            cond(HIGH, HIGH, lblLoop,  
                evt.dir=ENCODER_DIRECTION::LEFT;
                eventSystem.dispatchMessage(EventType::ENCODER_ROTATE,&evt);
                done= true;
            ) else cond(LOW, LOW, lblCCW1);
            break;
    }
    return done;
}
void EncoderRotate::execute() {
    static int newA=0;
    static int newB=0;
    static int pd=0;
    
    // static int left=0;
    TBT_THC(1,,
        TBT_IF(data.size()>0,
            TBT_BLOCK(
        
                pd=data.front(),
                // debug_printf("buffer size: %d\n",data.size()),
                data.pop(),
                newB=pd & 0b01,
                newA=(pd & 0b10)>>1,
                if ((currentA!=newA) || (currentB!=newB)) {
                    this->countRotate(newA,newB);
                },
                currentA=newA,
                currentB=newB,
            ),
        )
    )
}

 

void EncoderRotate::triggerA() {
    lastA=digitalRead(PIN_ENCODER_A);
    int v=0b100 | (lastB<<1) | lastA ;
    rotaryEncoder->data.push(v);
}
void EncoderRotate::triggerB() {
    lastB=digitalRead(PIN_ENCODER_B);
    int v=(lastB<<1) | lastA ;
    rotaryEncoder->data.push(v);
}