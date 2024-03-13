#pragma once
#include <Arduino.h>
#include "macro.h"



//copy(Array.from(new Array(20)).map((o,i)=>`#define FOREACH_${i}(na,FN, E, ...) case na-${i}: FN;ip=na-${i}; break; FOREACH_${i-1}(na,E, __VA_ARGS__)`).slice(1).join("\n"))

// #define FOREACH_3(FN, E, ...) case N_VA_ARGS(__VA_ARGS__)+1: FN; break; FOREACH_2(E, __VA_ARGS__)
// #define FOREACH_4(FN, E, ...) case N_VA_ARGS(__VA_ARGS__)+1: FN; break; FOREACH_3(E, __VA_ARGS__)
// #define FOREACH_5(FN, E, ...) case N_VA_ARGS(__VA_ARGS__)+1: FN; break; FOREACH_4(E, __VA_ARGS__)


#define __FOREACH__(prio,FN, NARGS, ...) \
    if (finished) return; \
    switch (ip) { \
        FOREACH_##NARGS(prio,NARGS,FN, __VA_ARGS__ ) \
        default: \
            if  (ip>MUL(NARGS,prio)) { \
                if (type==THREAD_EXECUTION::FOREVER ) ip=-1; \
                else finished=1; \
            } \
        break; \
    } \
    ip=ip+1; done=ip>=NARGS;

#define __FOREACH_(prio,FN, NARGS, ...) __FOREACH__(prio,FN, NARGS, __VA_ARGS__)
#define TBT_THC(prio,FN, ...)  __FOREACH_(prio,FN, N_VA_ARGS(__VA_ARGS__), __VA_ARGS__)

#define TBT_BLOCK(...) __VA_ARGS__
#define TBT_IF(labelNum,cond,trueCond,falseCond) \
    if (!(cond)) goto lbl__false_##labelNum; \
    ,trueCond,goto lbl__end_##labelNum \
    ,lbl__false_##labelNum: falseCond \
    ,lbl__end_##labelNum:


#define TBT_WHILE(labelNum,cond,body) TBT_BLOCK( \
    lbl__while_##labelNum: body, \
    if (cond) goto lbl__while_##labelNum; \
)

#define __TBT_DELAY(labelNum,FN,num)  time=FN; TBT_WHILE(labelNum,FN-time<num,;)

#define TBT_DELAY(labelNum,num) __TBT_DELAY(labelNum,millis(),num)

#define TBT_DELAY_MICRO(labelNum,num) __TBT_DELAY(labelNum,micros(),num)

#define TBT_WAIT_THREAD(labelNum,th) TBT_WHILE(labelNum,!(th.isFinished()),th.execute());

enum THREAD_EXECUTION {
    ONCE=1,
    FOREVER=2,
};
class BaseThread {
protected:
   
    /**
     * instruction pointer
    */
    int ip;
    /**
     * priority of the thread 1~N, max=maxInt/N
    */
    int priority;
    /**
     * isSuspend
    */
   bool isSuspend;
   uint32_t time;
   THREAD_EXECUTION type;
   int finished;

    /* when the last command execute then this value is true */
    bool done;

public:
    BaseThread();
    virtual ~BaseThread();
    int isFinished();
    /**
     * this is body of the thread, do not use any local variable here, if you want to, then create a function and call it
    */
    virtual  void execute()=0;
};

typedef void (*execution)();
class THFunc: public BaseThread {
private:
execution *callback;
    public:
    THFunc(execution *fn);
    void execute();
};
// void BaseThread::execute() {
//     if (isSuspend) return;
// }
