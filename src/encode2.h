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
class EncoderThread : public BaseThread
{
private:
    int currentA;
    int currentB;
    void applyChange();
    vector<std::function<void(int)>> callbacks;
   

public:
    
    queue<int> data;
  
public:
    ENCODER_DIRECTION dir;
    EncoderThread();
    // void setText(int x, int y, char *text);
    void execute();
    void onChange(std::function<void(int)> callback);
   
    
    static void triggerA();
    static void triggerB();
   
    // void initLcd();
};
extern EncoderThread *enc;