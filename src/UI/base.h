#pragma once
#include "tbt_thread.h"
#include "encode2.h"
#include "../mylcd.h"
#include "../eventData.h"


class BasePage: public BaseThread {
protected:
    bool isSuspend;
    // BasePage *lcd;
public:    
 bool ready=false;
    BasePage();
    bool drawTextSprite(uint16_t* buf,const char *text,int x,int y,int w,int h,int color);
    virtual bool render() { return false;};
    virtual bool handleEvent(EventData *dt)=0;
   
    // virtual bool onButtonTrigger(EventData *bt) { return false;};
};