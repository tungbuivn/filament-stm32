#pragma once
#include "tbt_thread.h"
#include "encode2.h"
class PageJump:public EventData {
public:
    int page;
};

class BasePage: public BaseThread {
protected:
    bool isSuspend;
public:    
    BasePage();
    virtual bool render() { return false;};
    virtual bool onClick() { return false;};
    virtual bool onRotate(ENCODER_DIRECTION dir) { return false;};
};