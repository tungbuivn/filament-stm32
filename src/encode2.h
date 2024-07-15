#pragma once
#include "tbt_thread.h"
#include <queue>
#include "events.h"
using namespace std;
enum ENCODER_DIRECTION {
    NONE_DIRECTION,
    LEFT,
    RIGHT
};
class EncoderData:public EventData {
public:
    ENCODER_DIRECTION dir;    
};

class EncoderClick : public BaseThread {
private:
    // vector<std::function<void()>> clicks;
public:
    void execute();
    // void onClick(std::function<void()> callback);
   
};
enum Stage
{
   
    lblLoop,
    lblCW,
    lblCW1,
    lblCW2,
    lblCW3,
    lblCCW,
    lblCCW1,
    lblCCW2,
    lblCCW3,
  

};
class EncoderRotate : public BaseThread
{
private:
    int currentA;
    int currentB;
   
    Stage phase;
  
   
    bool countRotate(int ra,int rb);
    queue<int> data;
    static void triggerA();
    static void triggerB();
public:
    
    EncoderRotate();
    // void setText(int x, int y, char *text);
    void execute() override;
   
   
};
// extern EncoderRotate *rotaryEncoder;