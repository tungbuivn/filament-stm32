#pragma once
#include "tbt_thread.h"
#include "base.h"

class HomePage : public BasePage {
public:
    HomePage(LCDThread* lcd);
    bool render() override;
    bool onClick() override;
    void execute() override;
    bool onRotate(ENCODER_DIRECTION dir) override;
    bool onButtonTrigger(EventData *bt) override;
    
};