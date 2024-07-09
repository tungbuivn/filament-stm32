
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
                TBT_WHILE(digitalRead(encClick)==HIGH,
                    TBT_DELAY(100)
                ),
                i=0,
                TBT_WHILE(i<clicks.size()-1,
                    clicks[i](),
                    i++,
                )
            )
            ,
        )
    )
}

EncoderThread::EncoderThread(): BaseThread(){ 
    // enc2=this;
    currentA=lastA;
    currentB=lastB;
    dir=ENCODER_DIRECTION::NONE;
    
    pinMode(encA,INPUT);
    pinMode(encB,INPUT);
    pinMode(encClick,INPUT);
    // sEncoder=this;
    attachInterrupt(digitalPinToInterrupt(encA), EncoderThread::triggerA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encB), EncoderThread::triggerB, CHANGE);
// // attachInterrupt(digitalPinToInterrupt(PA1), button_ISR2, FALLING);
// // attachInterrupt(digitalPinToInterrupt(PA2), button_ISR3, FALLING);
}
void EncoderThread::execute() {
    static int newA=0;
    static int newB=0;
    static int pd=0;
    static int count=0;
    static int i=0;
    
    // static int left=0;
    TBT_THC(5,,
        TBT_IF(data.size()>=1,
            TBT_BLOCK(
                pd=data.front(),
                data.pop(),
                newA=pd>>1,
                newB=pd & 0x0F,
               
                if ((currentA==1) && (currentB==1)) {
                    if ((newA==1) && (newB==0)) {
                        count--; // left
                        dir=ENCODER_DIRECTION::LEFT;
                    } else {
                        // right
                        count++;
                         dir=ENCODER_DIRECTION::RIGHT;
                    }
                } else if ((currentA==1) && (currentB==0)) {
                    
                    if ((newA==1) && (newB==1)) {
                        // right
                         dir=ENCODER_DIRECTION::RIGHT;
                    } else {
                        // left
                         dir=ENCODER_DIRECTION::LEFT;
                    }
                } else if ((currentA==0) && (currentB==1)) {
                    if ((newA==0) && (newB==0)) {
                        // right
                         dir=ENCODER_DIRECTION::RIGHT;
                    } else {
                        // left
                         dir=ENCODER_DIRECTION::LEFT;
                    }
                } else { // 0,0
                    if ((newA==1)&&(newB==0)) {
                        // right
                         dir=ENCODER_DIRECTION::RIGHT;
                    } else {
                        // left
                         dir=ENCODER_DIRECTION::LEFT;
                    }
                },
                // process on change direction
                i=0,
                TBT_WHILE(i<callbacks.size()-1,
                    callbacks[i](dir),
                    i++,
                )
            ),
        )
    )
    
   
}
void EncoderThread::onChange(std::function<void(int)> callback) {
    callbacks.push_back(callback);
}
 

void EncoderThread::triggerA() {
    lastA=!lastA;
    int v=(lastA<<1) | lastB ;
    enc->data.push(v);
}
void EncoderThread::triggerB() {
    lastB=!lastB;
    int v=(lastA<<1) | lastB ;
    enc->data.push(v);
}