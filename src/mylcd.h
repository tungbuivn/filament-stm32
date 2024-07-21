#pragma once
#include "tbt_thread.h"
#include <queue>
#include "encode2.h"
#include "TFT_eSPI.h"
// #include "FreeSansBold40pt7b.h"
#include "FreeSansBold45pt7b.h"
// #include "Fonts/GFXFF/"
#include "icon20pt7b.h"
// #define FS7pt &FreeSans7pt
#define FS9pt &FreeSans9pt7b
// #define FS12pt &FreeSans12pt7b
// #define FSB40pt &FreeSansBold40pt7b
#define FSB45pt &FreeSansBold45pt7b
#define FSI30pt &icon20pt7b
const uint8_t gradientSpeed[] PROGMEM ={
    0xe0, 0x07, 0xc0, 0x0f, 0xa0, 0x17, 0x80, 0x1f, 0x60, 0x27, 0x40, 0x27, 0x00, 0x2f, 0xe0, 0x36, 0xc0, 0x3e, 0xa0, 0x46, 0x80, 0x46, 0x60, 0x4e, 0x20, 0x56, 0x00, 0x5e, 0xe0, 0x65, 0xc0, 0x65, 0xa0, 0x6d, 0x80, 0x75, 0x60, 0x7d, 0x20, 0x85, 0x00, 0x85, 0xe0, 0x8c, 0xc0, 0x94, 0xa0, 0x9c, 0x80, 0xa4, 0x60, 0xa4, 0x20, 0xac, 0x00, 0xb4, 0xe0, 0xbb, 0xc0, 0xc3, 0xa0, 0xc3, 0x80, 0xcb, 0x60, 0xd3, 0x20, 0xdb, 0x00, 0xdb, 0xe0, 0xe2, 0xc0, 0xea, 0xa0, 0xf2, 0x60, 0xfa, 0x40, 0xfa
}; 
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

    // queue<TextQueueData*> data;
    // void updateText();
    // int init=0;
   
    void initTFT();
    // static void setPwmText(const char *text);
    // static bool UpdatePwm(EventData *data);
    // static bool OffPwm(EventData *data);
    // static bool onEncoderClick(EventData *data);
    // int queueLen;
public:
    TFT_eSPI *tft;
    // LCDTBT *dbg;
    LCDThread();
    // void setText(int x, int y, char *text);
    void execute() override;
    // void initLcd();
};
extern LCDThread *mylcd;