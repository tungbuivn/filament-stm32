
#include "tbt_thread.h"
BaseThread::BaseThread() {
    this->ip=0;
    priority=5;
    type=THREAD_EXECUTION::FOREVER;
    finished=0;
};
BaseThread::~BaseThread() {

}
int BaseThread::isFinished() {
    return finished;
}