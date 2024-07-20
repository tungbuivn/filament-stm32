#include "home.h"
#include "TFT_eSPI.h"
#include "../settings.h"

HomePage::HomePage() : BasePage()
{
}

void HomePage::drawSwingThread(ThreadData *data) {
    AUTO_THC(data,
        TBT_IF_TRUE(settings->started && settings->swing,
            drawSwing(settings->swing),
            TBT_DELAY(10),
        )
    )
}
void HomePage::drawOnOffThread(ThreadData *data) {
    AUTO_THC(data,
        TBT_IF_TRUE(settings->started,
            drawOnOff(settings->started),
            TBT_DELAY(10),
        )
    )
   
}
void HomePage::execute()
{
    static ThreadData swingTh;
    static ThreadData onOffTh;
    
   

    TBT_THC(5,
        drawSwingThread(&swingTh),
        drawOnOffThread(&onOffTh),
    )
}
bool HomePage::handleEvent(EventData *dt)
{
    if (!ready && dt->type!=EventType::RENDER) return false;
    auto mt = (MotorPwmData *)dt;
    switch (dt->type)
    {
    case EventType::ENCODER_ROTATE:

        if (settings->started)
        {
            debug_printf("home rotated !\n");
            eventSystem.dispatchMessage(EventType::SETTINGS_UPDATE_GEAR, dt);
        }

        return false;

        break;
    case EventType::GEAR_UPDATED:
        if (settings->started)
        {
            auto te = (GearData *)dt;
            drawGear(te->gear);
        }
        return false;
        break;
    case EventType::ENCODER_CLICK:
    {
        PageJump pg;
        pg.page = 1;
        eventSystem.dispatchMessage(EventType::GOTO_PAGE, &pg);
        return true;
    }
    break;
    case EventType::RENDER:
        render();
        break;
    case EventType::PWM_UPDATED:
        if (settings->started) {
            
                // int freq = settings->minFreq + (settings->gear * (settings->maxFreq - settings->minFreq) / settings->maxGear);
                drawFreq(settings->pwmFrequency());
                drawPwm(settings->pwmDuty());
                    
            
            
        }
            

        break;
    case EventType::TEMPERATURE_CHANGE:
    {
        auto te = (TemperatureData *)dt;
        // debug_printf("pwm update !\n");

        drawTemp(te->temperature);
    }

    break;
    case EventType::ON_OFF_UPDATED:
    {
        int state=((OnOffData*)dt)->state;
        debug_printf("draw on/off %d\n",state);
        if (state==0) {
             drawGear(0);
             drawPwm(0);
        } else {
             drawGear(settings->gear);
             drawPwm(settings->pwmDuty());
             
        }
        drawFreq(settings->pwmFrequency());
        drawOnOff(state);
        drawSwing(0);
    }
    
        break;
    case EventType::SWING_UPDATED:
        drawSwing(settings->swing);
        break;
    default:
        break;
    }
    return false;
};
void HomePage::drawOnOff(int state) {
    // TFT_eSprite leaf=TFT_eSprite(mylcd->tft);
    auto draw = [](BaseSprite *bs, TFT_eSprite *sp, int state)
    {
        if (state) {
            // sp->fillSmoothCircle(bs->w/2,bs->h/2,20,TFT_ORANGE);
            sp->setFreeFont(FSI30pt);
            sp->setTextColor(TFT_GREEN);
            sp->setTextDatum(MC_DATUM);
            // sprintf(buf, "%d*C", tempVal);
            sp->drawString("0", bs->w / 2, bs->h / 2, 1);
        }
        
        // leaf->setColorDepth(1);
        // leaf->createSprite(17, 20);
        // leaf->fillSprite(0);
        // leaf->drawSmoothArc(17/2,20,20,0,115,65,1,0);
        // leaf->setBitmapColor(TFT_RED, 0);
        // // leaf->setPivot()
        // debug_printf("begin draw temp");
        // // leaf->pushToSprite(sp,bs->w/2,bs->h/2);
        // leaf->pushRotated(sp,0);
        // sp->pushRotated(10,)
       
        debug_printf("done draw on off");
    };

  
    DRAW_ROTATE_SPRITE(startStop,1, state);
   
        
        // delete leaf;
   
}
void HomePage::drawSwing(int state)
{
    auto draw = [](BaseSprite *bs, TFT_eSprite *sp, int state)
    {
        if (settings->started && settings->swing)
        {
            sp->setFreeFont(FSI30pt);
            sp->setTextColor(TFT_GREEN);
            sp->setTextDatum(MC_DATUM);
            sp->drawString("1", bs->w / 2, bs->h / 2, 1);
        }
    };

    DRAW_ROTATE_SPRITE(swing,-1, state);
}
void HomePage::drawTemp(int tempVal)
{
    auto draw = [](BaseSprite *temp, TFT_eSprite *sp, int tempVal)
    {
        char buf[20] = {};
        debug_printf("begin draw temp");
        sp->setFreeFont(FS9pt);
        sp->setTextColor(TFT_WHITE);
        sp->setTextDatum(MC_DATUM);
        sprintf(buf, "%d*C", tempVal);
        sp->drawString(buf, temp->w / 2, temp->h / 2, 1);
        // sp->drawNumber(123,temp->w/2,temp->h/2,1);
        debug_printf("done draw temp");
    };

    if (lastTemp != tempVal)
    {
        lastTemp = tempVal;

        DRAW_SPRITE(temp, tempVal)
    }
}
void HomePage::drawPwm(int pwm)
{
    auto draw = [](BaseSprite *bs, TFT_eSprite *sp, int pwm)
    {
        debug_printf("begin update pwm");
        sp->setFreeFont(FS9pt);
        sp->setTextColor(TFT_ORANGE);
        sp->setTextDatum(MC_DATUM);
        char buf[15];
        sprintf(buf,"%d%%",(int)(pwm*100/(MAX_PWM_DUTY-1)));

        sp->drawString(buf, bs->w / 2, bs->h / 2, 1);
        debug_printf("done update pwm");
    };

    if (lastPwm != pwm)
    {

        lastPwm = pwm;
        // auto sp = pwmSpeed->sp;
        DRAW_SPRITE(pwmSpeed, pwm)
    }
}
void HomePage::drawGear(int gear)
{
    auto draw = [](BaseSprite *bs, TFT_eSprite *sp, int val)
    {
        debug_printf("begin update gear");
        sp->setFreeFont(FSB45pt);
        sp->setTextColor(TFT_GREEN);
        sp->setTextDatum(MC_DATUM);

        sp->drawNumber(val, bs->w / 2, bs->h / 2, 1);
        debug_printf("done update gear");
    };

    if (lastGear != gear)
    {

        lastGear = gear;
        // auto sp = pwmSpeed->sp;
        DRAW_SPRITE(gearSpeed, gear)
    }
}
void HomePage::drawFreq(int freq) {
    auto draw = [](BaseSprite *bs, TFT_eSprite *sp, int val)
    {
        debug_printf("begin update freq");
        sp->setFreeFont(FS9pt);
        sp->setTextColor(TFT_WHITE);
        sp->setTextDatum(MC_DATUM);
        char buf[20]={};
        sprintf(buf,"%d Hz",val);
        sp->drawString(buf, bs->w / 2, bs->h / 2, 1);
        debug_printf("done update freq");
    };

    if (lastFreq != freq)
    {

        lastFreq = freq;
        // auto sp = pwmSpeed->sp;
        DRAW_SPRITE(freqSpeed, freq)
    }
}

bool HomePage::render()
{
    lastTemp = -1;
    lastPwm = -1;
    lastGear = -1;
    lastFreq = -1;
    debug_printf("render from home page");
    auto tft = mylcd->tft;
    tft->fillScreen(TFT_BLACK);
    tft->fillSmoothCircle(120, 112, 100, TFT_WHITE);
    tft->fillSmoothCircle(120, 112, 90, TFT_PURPLE);

    tft->setFreeFont(FSB40pt);
    tft->setTextDatum(MC_DATUM);

    tft->setTextColor(TFT_WHITE);
    tft->setFreeFont(&FreeSans9pt7b);
    tft->drawString(F("Speed"), 92 + 28, 35 + 17, 1);

    if (!gearSpeed)
        gearSpeed = new BaseSprite(70, 75, 100, 74);
    drawGear(settings->gear);
    
    if (!pwmSpeed)
        pwmSpeed = new BaseSprite(96, 163, 48, 26);
    drawPwm(settings->pwmDuty());

    
    tft->setFreeFont(FSI30pt);
    tft->setTextDatum(ML_DATUM);
    tft->setTextColor(TFT_BLUE);
    tft->drawString("2", 184, 264);

    if (!temp)
        temp = new BaseSprite(184, 284, 46, 26);
    drawTemp(0);
    // if (!tempBuf)
    // {
    //     tempBuf = (uint16_t *)malloc(((30) + 2) * ((30) + 2) * 2);
    //     tft->readRect(178, 264, 30, 30, tempBuf);
    // }
    tft->setFreeFont(FSI30pt);
    tft->setTextDatum(ML_DATUM);
    tft->setTextColor(TFT_YELLOW);
    tft->drawString("3", 10, 260);

    if (!freqSpeed)
        freqSpeed = new BaseSprite(10, 284, 56, 26);
    drawFreq(settings->pwmFrequency());

    // tft->setTextDatum(ML_DATUM);
    // tft->fillRect(10, 264, 30, 30, TFT_YELLOW);
    // tft->drawString("000%", 10, 278);

    if (!startStop)
        startStop=new BaseSprite(95,268,45,45);
    drawOnOff(settings->started);
    
    if (!swing)
        swing=new BaseSprite(95,218,45,45);
    drawSwing(settings->swing);
   
    // ready=true;
    return false;
};
// bool HomePage::onButtonTrigger(EventData *bt)
// {
//     return false;
// };