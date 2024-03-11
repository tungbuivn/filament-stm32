#pragma once
#include "tbt_thread.h"
#include <queue>
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
    // int queueLen;
public:
    LCDThread();
    void setText(int x, int y, char *text);
    void execute();
    void initLcd();
};
extern LCDThread mylcd;