#include "home.h"
HomePage::HomePage(LCDThread* lcd):BasePage(lcd) {

}

void HomePage::execute() {
    TBT_THC(1,
    )
}
bool HomePage::onClick() {
    PageJump pg;
    pg.page=1;
    eventSystem.dispatchMessage(EventType::GOTO_PAGE,&pg);
    return true;
}
bool HomePage::onRotate(ENCODER_DIRECTION dir) {

}

bool HomePage::render() { 
   
    return false;
};
bool HomePage::onButtonTrigger(EventData *bt) {
    return false;
};