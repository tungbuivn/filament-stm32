#pragma once
#include "tbt_thread.h"
#include "events.h"
using namespace std;



class TemperatureData: public EventData {
public:
    int temperature;
};

class Temperature : public BaseThread {


public:    
    Temperature();
   
    void execute();
};