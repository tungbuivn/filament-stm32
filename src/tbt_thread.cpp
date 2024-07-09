// #pragma once
#include "tbt_thread.h"
BaseThread::BaseThread() {
   
   ip=0;
   priority=5;
   type=THREAD_EXECUTION::FOREVER;
   finished=0;
//    done=0;
};
// ThreadAction::ThreadAction(ThreadCallBack cb) {
//     this->cb=cb;
// }
// void ThreadAction::execute() {
//     this->cb();
// }
int BaseThread::isFinished() {
    return finished;
}