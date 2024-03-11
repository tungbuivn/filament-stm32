#pragma once
#include "tbt_thread.h"
class Temperature : public BaseThread {
public:    
    Temperature();
    void execute();
};