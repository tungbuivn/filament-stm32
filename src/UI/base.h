#pragma once
#include "tbt_thread.h"
#include "encode2.h"
#include "../mylcd.h"
class PageJump:public EventData {
public:
    int page;
};

class BasePage: public BaseThread {
protected:
    bool isSuspend;
    BasePage *lcd;
public:    
    BasePage(LCDThread* lcd);
    virtual bool render() { return false;};
    virtual bool onClick() { return false;};
    virtual bool onRotate(ENCODER_DIRECTION dir) { return false;};
    virtual bool onButtonTrigger(EventData *bt) { return false;};
};