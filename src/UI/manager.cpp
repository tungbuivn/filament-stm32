#include "manager.h"
#include "../events.h"
#include "../buttons.h"
#include "setup.h"

// LCDThread* lcd=NULL;
// Settings *settings=NULL;
// bool inited=false;
ManagerPage::ManagerPage()
{
    // lcd=alcd;
    // settings=asettings;

    page = 0;

    
    // man = this;
    // eventSystem.addListener(EventType::BUTTON_TRIGGER,ManagerPage::onButtonTrigger);
    // isSuspend = true;
}
void ManagerPage::init()
{
    pages.assign({
        // new SetupPage(),
                  new HomePage(),
                  new SetupPage()}
                  );
    eventSystem.addListener(EventType::GOTO_PAGE, ManagerPage::gotoPage);

    eventSystem.addListener(EventType::ENCODER_ROTATE, ManagerPage::handler);
    eventSystem.addListener(EventType::ENCODER_CLICK, ManagerPage::handler);
    eventSystem.addListener(EventType::RENDER, ManagerPage::handler);
    eventSystem.addListener(EventType::PWM_UPDATED, ManagerPage::handler);
    eventSystem.addListener(EventType::GEAR_UPDATED, ManagerPage::handler);
    eventSystem.addListener(EventType::TEMPERATURE_CHANGE, ManagerPage::handler);
    eventSystem.addListener(EventType::TEMPERATURE_UPDATED, ManagerPage::handler);

    
    eventSystem.addListener(EventType::ON_OFF_UPDATED, ManagerPage::handler);
    eventSystem.addListener(EventType::SWING_UPDATED, ManagerPage::handler);
    currentPage = pages[0];
    inited=true;
}
bool ManagerPage::handler(EventData *dt)
{
    if (!dt)
        return false;
    bool rs;
    if (man)
    {
        if (settings->sleepRemain == 0)
        {
            man->isSleep = 1;
        }
        if (man->isSleep && dt->type == ENCODER_CLICK)
        {
            man->isSleep = 0;
        }
        else

            if (dt->type == EventType::RENDER || man->currentPage->ready)
        {
            rs = man->currentPage->handleEvent(dt);
            man->currentPage->ready = true;
        }

        // auto pg=man->pages.at(man->page);

        return rs;
    }
    return false;
}

void ManagerPage::execute()
{
    if (!inited) return;
    static BasePage *pg = NULL;
    TBT_THC(1,

            pages.at(page)->execute(),

    )
}
// bool ManagerPage::onButtonTrigger(EventData *dt) {
//      if (!man) return false;
//     // auto ec=(EncoderData*)dt;
//     return man->pages.at(man->page)->onButtonTrigger(dt);

// };

// bool ManagerPage::onRotate(EventData *dt)
// {
//     if (!man)
//         return false;
//     auto ec = (EncoderData *)dt;
//     return man->pages.at(man->page)->handleEvent(ec);
// }
bool ManagerPage::gotoPage(EventData *dt)
{
    if (!man)
        return false;
    man->currentPage->ready = false;
    man->currentPage->removeSprite();
    // if (man->isSuspend) return false;
    PageJump *pg = (PageJump *)dt;
    man->page = pg->page;
    man->currentPage = man->pages.at(pg->page);
    // man->currentPage->ready=false;
    EventEmpty ev;
    eventSystem.dispatchMessage(EventType::RENDER, &ev);
    // man->isSuspend=true;
    // man->page=pg->page;
    return false;
}