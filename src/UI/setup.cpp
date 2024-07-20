#include "setup.h"

SetupPage::SetupPage() : BasePage()
{
}
void SetupPage::execute()
{
}
bool SetupPage::render()
{
    auto tft = mylcd->tft;
    tft->fillScreen(TFT_BLACK);
    tft->fillSmoothCircle(120, 112, 100, TFT_WHITE);
    tft->fillSmoothCircle(120, 112, 90, TFT_RED);
    return false;
};

bool SetupPage::handleEvent(EventData *dt)
{
    switch (dt->type)
    {
   
    case EventType::ENCODER_CLICK:
    {
        PageJump pg;
        pg.page = 0;
        eventSystem.dispatchMessage(EventType::GOTO_PAGE, &pg);
        return true;
    }
    break;
    case EventType::RENDER:
        render();
        break;
    
    default:
        break;
    }
    return false;
}