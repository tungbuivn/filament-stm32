
#include "tbt_thread.h"
BaseThread::BaseThread() {
    this->ip=0;
    priority=5;
    type=THREAD_EXECUTION::FOREVER;
    finished=0;
    done=0;
};
BaseThread::~BaseThread() {

}
int BaseThread::isFinished() {
    return finished;
}

THFunc::THFunc(execution *fn) {
    callback=fn;
}
void THFunc::execute() {
    (*callback)();
}