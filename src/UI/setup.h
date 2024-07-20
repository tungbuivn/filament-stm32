
#pragma once
#include "base.h"
class SetupPage : public BasePage
{
public:
    SetupPage();
    void execute() override;
    bool render() override;
    bool handleEvent(EventData* dt) override;
};