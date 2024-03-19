#pragma once

#include "tbt_thread.h"
#include <queue>

class LedBlink : public BaseThread
{
private:
    
    // int queueLen;
public:
  
    void init();
    void execute();
};
extern LedBlink ledBlink;