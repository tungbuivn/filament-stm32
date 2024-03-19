#pragma once
#include <tbt_thread.h>
#include <queue>
#include "Adafruit_GFX.h"
#include <ST7567S-IIC-128x64.h>
using namespace std;
struct TextQueueData
{
    int x;
    int y;
    char *text;
};
class LCDRender:public BaseThread {
public:
int row;
int col;
    queue<bool> needUpdate;
    LCDRender();
    void execute();
};
class LCDThread : public BaseThread
{
private:
    queue<int> data;
    int lastTemp=-999;
    bool needUpdate=false;
    void updateText();
    // int init=0;
    int row=0;
    int col;
    LCDRender rd;
    // int queueLen;
public:
    LCDThread();
    void setText(int x, int y, char *text);
    void setTemp(int t);
    void execute();
    void init();
};
extern LCDThread mylcd;
extern GFXfont font;
extern ST7567S_IIC Lcd7567;