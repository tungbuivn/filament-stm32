#include "home.h"

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