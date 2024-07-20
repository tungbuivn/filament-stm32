#pragma once
#include "tbt_thread.h"
#include <queue>
#include "encode2.h"
#include "TFT_eSPI.h"
#include "FreeSansBold40pt7b.h"
#include "FreeSansBold45pt7b.h"
#include "icon20pt7b.h"
#define FS9pt &FreeSans9pt7b
#define FS12pt &FreeSans12pt7b
#define FSB40pt &FreeSansBold40pt7b
#define FSB45pt &FreeSansBold45pt7b
#define FSI30pt &icon20pt7b

// #include "dbglcd.h"

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
   
    void initTFT();
    static void setPwmText(const char *text);
    static bool UpdatePwm(EventData *data);
    static bool OffPwm(EventData *data);
    // static bool onEncoderClick(EventData *data);
    // int queueLen;
public:
    TFT_eSPI *tft;
    // LCDTBT *dbg;
    LCDThread();
    void setText(int x, int y, char *text);
    void execute() override;
    // void initLcd();
};
extern LCDThread *mylcd;