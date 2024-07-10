
// #pragma once
#include "encode2.h"
#include <Arduino.h>
#include "tbt_thread.h"
#include <vector>
#include <functional>
#include "pins.h"

// #include <Encoder.h>

static  int lastA=HIGH;
static  int lastB=HIGH;
static  int adir=0;
// Encoder myEnc(encA, encB);
// EncoderThread* sEncoder=0;
void EncoderClick::onClick(std::function<void()> callback) {
    clicks.push_back(callback);
}
   
void EncoderClick::execute() {
    static int state=0;
    static int i=0;
    state=digitalRead(encClick);
    TBT_THC(5,,
        TBT_IF(state==HIGH,
            TBT_BLOCK(
                debug_printf("Initialized encoder: %d %d\n",digitalRead(encA),digitalRead(encB)),
                
                Serial.println("Encoder clicked"),
                TBT_WHILE(digitalRead(encClick)==HIGH,
                    // TBT_DELAY(100)
                ),
                Serial.print("Click callbacks:"),
                Serial.println(clicks.size()),
                TBT_IF_TRUE(clicks.size()>0,
                    i=0,
                    TBT_WHILE(i<clicks.size()-1,
                        clicks[i](),
                        i++,
                    )
                ) 
                
            )
            ,
        )
    )
}
// right direction
// 1 1
// 0 1
// 1 1
// 0 1
// 1 1

// A B  
// 0 1 CW

// 1 1

// 1 0 CCW

// left direction

EncoderThread::EncoderThread(): BaseThread(){ 
    // enc2=this;
    currentA=lastA;
    currentB=lastB;
    dir=ENCODER_DIRECTION::NONE;
     phase = lblInit;

    pinMode(encA,INPUT);
    pinMode(encB,INPUT);
    pinMode(encClick,INPUT);
   
    // sEncoder=this;
    attachInterrupt(digitalPinToInterrupt(encA), EncoderThread::triggerA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encB), EncoderThread::triggerB, CHANGE);
// // attachInterrupt(digitalPinToInterrupt(PA1), button_ISR2, FALLING);
// // attachInterrupt(digitalPinToInterrupt(PA2), button_ISR3, FALLING);
}

#define cond(x, y, p, ...)      \
    if ((ra == x) && (rb == y)) \
    {                           \
        phase = p;              \
        __VA_ARGS__;            \
    }

ENCODER_DIRECTION EncoderThread::countRotate(int ra,int rb)
{
   
    // readData;
    switch (phase)
    {
    case lblInit:
        // lblInit
        roLeft = roRight = false;
        dir = ENCODER_DIRECTION::NONE;
        cond(HIGH, HIGH, lblLoop);
        // phase = lblLoop;
        break;
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
        cond(HIGH, HIGH, lblDone; dir = ENCODER_DIRECTION::LEFT;) else cond(LOW, LOW, lblCW1);
        break;
    // CCW ?
    case lblCCW: // HIGH_LOW
        cond(LOW, LOW, lblCCW1) else cond(HIGH, HIGH, lblLoop);
        break;
    case lblCCW1: // LOW_LOW
        cond(LOW, HIGH, lblCCW2) else cond(HIGH, LOW, lblCCW);
        break;
    case lblCCW2: // LOW_HIGH
        cond(HIGH, HIGH, lblDone, dir = ENCODER_DIRECTION::RIGHT;) else cond(LOW, LOW, lblCCW1);
        break;

    case lblDone:
       
        {
            phase = lblInit;
          
        }
        break;
    default:
        break;
    }
    return dir;
}
void EncoderThread::execute() {
    static int newA=0;
    static int newB=0;
    static int pd=0;
    static int count=0;
    static int i=0;
    static ENCODER_DIRECTION ret=ENCODER_DIRECTION::NONE;
   
     static int CW=1;
     static int CCW=1;
    
    // static int left=0;
    TBT_THC(1,,
        TBT_IF(data.size()>0,
            TBT_BLOCK(
                // count=count%4,
                pd=data.front(),
                // debug_printf("buffer size: %d\n",data.size()),
                data.pop(),
                newA=pd & 0b01,
                    
                
                newB=(pd & 0b10)>>1,
                // TBT_IF_FALSE((newA==1))
                ret=this->countRotate(newA,newB),
                if (ret==ENCODER_DIRECTION::LEFT) {
                    debug_printf("Left\n");
                } else if (ret== ENCODER_DIRECTION::RIGHT) {
                    debug_printf("Right\n");
                },
            
                   
                
                TBT_IF_TRUE(callbacks.size()>0,
                    i=0,
                    TBT_WHILE(i<callbacks.size()-1,
                        callbacks[i](dir),
                        i++,
                    )
                )
                
            ),
        )
    )
    
   
}
void EncoderThread::onChange(std::function<void(int)> callback) {
    callbacks.push_back(callback);
}
 

void EncoderThread::triggerA() {
    // adir=1;
    int na=digitalRead(encA);
    if (na!=lastA) {
        lastA=na;    
        int v=0b100 | (lastB<<1) | lastA ;
        enc->data.push(v);
    }
    
}
void EncoderThread::triggerB() {
    int nb=digitalRead(encB);
    if (nb!=lastB) {
        lastB=nb;
        int v=(lastB<<1) | lastA ;
        enc->data.push(v);
    }
    
   
}