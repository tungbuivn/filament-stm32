#include "manager.h"
#include "../events.h"
#include "../buttons.h"
ManagerPage* man=NULL;
ManagerPage::ManagerPage(){
    man=this;
    page=0;
    pages.push_back(new HomePage());
    eventSystem.addListener(EventType::ENCODER_ROTATE,ManagerPage::onRotate);
    eventSystem.addListener(EventType::ENCODER_CLICK,ManagerPage::onClick);
    eventSystem.addListener(EventType::GOTO_PAGE,ManagerPage::gotoPage);
    eventSystem.addListener(EventType::ONOFF_BUTTON,ManagerPage::onOffStateChange);
}
bool ManagerPage::onClick(EventData *dt) {
    if (man && !man->isSuspend) {
       return man->pages.at(man->page)->onClick();
    }
    return false;
}
void ManagerPage::execute() {
    static BasePage *pg=NULL;
    TBT_THC(1,
        pg = pages.at(page),
        TBT_IF(isSuspend,
            TBT_BLOCK(
                TBT_WHILE(!pg->render(),),
                isSuspend=false,
            ),
            TBT_BLOCK(
                pages.at(page)->execute(),
            )
        )
       
    )
}
bool ManagerPage::onOffStateChange(EventData* dt) {
    if (!man) return false;
    if (man->isSuspend) return false;
    OnOffState *st=(OnOffState*)dt;
    if (st->isOn) {

    } else {
        
    }
}
bool ManagerPage::onRotate(EventData* dt) {
    if (!man) return false;
    if (man->isSuspend) return false;
    PageJump* pg=(PageJump*)dt;
    man->isSuspend=true;
    man->page=pg->page;
    return false;
}
bool ManagerPage::gotoPage(EventData* dt) {
    if (!man) return false;
    if (man->isSuspend) return false;
    PageJump* pg=(PageJump*)dt;
    man->isSuspend=true;
    man->page=pg->page;
    return false;
}