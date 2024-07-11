#pragma once
#include "tbt_thread.h"
#include <queue>
#include "encode2.h"
#include "dbglcd.h"

using namespace std;
struct TextQueueData
{
    int x;
    int y;
    char *text;
};
class LCDThread : public BaseThread
{
private:

    queue<TextQueueData*> data;
    void updateText();
    int init=0;
    static void onEncoderChange(int dir);
    static void onEncoderClick();
    // int queueLen;
public:
    // LCDTBT *dbg;
    LCDThread(EncoderThread *rotaryEncoder,EncoderClick *encoderButton);
    void setText(int x, int y, char *text);
    void execute();
    void initLcd();
};
extern LCDThread *mylcd;