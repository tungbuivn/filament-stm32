#pragma once
#include "tbt_thread.h"
#include "base.h"

class HomePage : public BasePage {
public:
    bool onClick() override;
    void execute() override;
    bool onRotate(ENCODER_DIRECTION dir) override;
};