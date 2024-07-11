#pragma once
#include "tbt_thread.h"
#include <queue>
using namespace std;
enum ENCODER_DIRECTION {
    NONE=0,
    LEFT=1,
    RIGHT=2
};
struct EncoderData
{
    int a;
    int b;
    EncoderData *next;    
};

class EncoderClick : public BaseThread {
private:
    vector<std::function<void()>> clicks;
public:
    void execute();
    void onClick(std::function<void()> callback);
   
};
enum stage
{
    lblInit = 0,
    lblLoop,
    lblCW,
    lblCW1,
    lblCW2,
    lblCW3,
    lblCCW,
    lblCCW1,
    lblCCW2,
    lblCCW3,
    lblDone

};
class EncoderThread : public BaseThread
{
private:
    int currentA;
    int currentB;
    void applyChange();
    vector<std::function<void(int)>> callbacks;
   stage phase;
    bool roLeft ;
    bool roRight;

public:
    
    queue<int> data;
  
public:
    ENCODER_DIRECTION dir;
    EncoderThread();
    ENCODER_DIRECTION countRotate(int ra,int rb);
    // void setText(int x, int y, char *text);
    void execute();
    void onChange(std::function<void(int)> callback);
   
    
    static void triggerA();
    static void triggerB();
   
    // void initLcd();
};
extern EncoderThread *rotaryEncoder;