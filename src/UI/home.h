#pragma once
#include "tbt_thread.h"
#include "base.h"
#include "TFT_eSPI.h"
#include "base-sprite.h"

class HomePage : public BasePage
{

    // BaseSprite *pwm;

    BaseSprite *pwmSpeed = NULL;
    BaseSprite *gearSpeed = NULL;
    BaseSprite *startStop = NULL;
     BaseSprite *swing = NULL;
    // uint16_t* pwmSpeedBuf=NULL;

    BaseSprite *temp = NULL;
    BaseSprite *freqSpeed = NULL;
    // uint16_t* tempBuf=NULL;

    int lastTemp = -1;
    int lastPwm = -1;
    int lastGear = -1;
    int lastFreq = -1;
    void drawPwm(int pwmValue);
    void drawGear(int gear);
    void drawTemp(int tempVal);
    void drawFreq(int afreq);
    void drawOnOff(int state);
    void drawSwing(int state);
    void drawSwingThread(ThreadData *data) ;
    void drawOnOffThread(ThreadData *data) ;

public:
    HomePage();
    bool render() override;

    void execute() override;
    bool handleEvent(EventData *dt) override;

    // bool onButtonTrigger(EventData *bt) override;
};