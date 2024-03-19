
#include "mylcd.h"
#include <tbt_thread.h>
#include <Arduino.h>
// #include <U8g2lib.h>
#include <Wire.h>
// #include <lcd.h>
#include "ST7567S-IIC-128x64.h"
#include <ttf/arial6pt7b.h>

#define LCD_SCL PB6
#define LCD_SDA PB7

GFXfont font = arial6pt7b;

//
// U8G2_ST7567_ENH_DG128064I_F_HW_I2C   u8g2(U8G2_R0,U8X8_PIN_NONE,SCL,SDA);

#define LCD_WIDTH 128
#define LCD_HEIGHT 64
// ST7567_128
// create an lcd object.
ST7567S_IIC Lcd7567(LCD_WIDTH, LCD_HEIGHT);

LCDRender::LCDRender()
{
    row = 0;
    col = 0;
}
void LCDRender::execute()
{
    //  Lcd7567.render();
    TBT_THC(
        5, , ,
        if (needUpdate.size()) {
            while (needUpdate.size())
                needUpdate.pop();
            row = 0;

            // needUpdate=false;
        },
        //   if (row>=)
        TBT_DELAY(100), );
}
// lcd  lcd;
LCDThread::LCDThread() : BaseThread()
{
    rd.needUpdate.push(0);
    //     //  Lcd.Init();

    //   lcd.testPixel(2);
    // Lcd7567.draw_circle(105, 30, 15, DRAW_ALL, false, true);
    // queueLen=0;
    // int x=SCL;
    //  Wire.setSDA(SDA);
    // Wire.setSCL(SCL);
    //  u8g2.setI2CAddress(0x3F);

    //     u8g2.setBusClock(400000);
    //     u8g2.begin();
    //     u8g2.clearBuffer();
    //      u8g2.setFont(u8g2_font_ncenB14_tr);
    //     u8g2.drawStr(2,20,"Hello world");

    //      int x=0;
    //       for (x = 0; x < 99; x++)
    //   {
    //       u8g2.clearBuffer();
    //       u8g2.setCursor(15,23);
    //       u8g2.print(x);
    //       u8g2.sendBuffer();
    //   }
};
void LCDThread::setText(int x, int y, char *atext)
{

    TextQueueData *c = new TextQueueData();
    std::string s(atext);
    // do something with s
    c->text = new char[s.size()]; // memory allocated
    strcpy(c->text, s.c_str());

    c->x = x;
    c->y = y;

    // Serial.println("=====");
    // Serial.println(c->text);
    // c->text = text;
    // data.push(c);
}
void LCDThread::setTemp(int t)
{
    if (t != lastTemp)
    {
        lastTemp = t;
        needUpdate = true;
    }
    // data.push(t);
    // int *buf=malloc(50);
    // sprintf(buf, "Temperature: %3f",t);
}

void LCDThread::updateText()
{
    // if (data.size()>0) {

    // int inf;
    // while (data.size()) {

    //    inf=data.front();
    //      data.pop();
    // }
    // Serial.print("Update text lcd: ");
    // Serial.println(inf->text);
    // Lcd7567.setCursor(inf->x, inf->y);                    //Character display position. y=0-3, x=0-17
    char buf[20];
    sprintf(buf, "Temp: %8d", lastTemp);
    Lcd7567.fillRect(20, 0, 127, 16, 0);
    Lcd7567.setCursor(0, font.yAdvance);
    Lcd7567.print(buf);
    // rd.needUpdate.push(0);
    // Lcd7567.render();
    // Lcd7567.

    // delete[] inf->text;
    // delete inf;

    // }
}

void LCDThread::init()
{
    Lcd7567.Init();

    Lcd7567.fillScreen(0xff);
    Lcd7567.setRotation(0);
    Lcd7567.setFont(&font);

    //      Lcd7567.drawRect(10,10,50,30,1);
    //     // Lcd7567.drawPixel(1,1,1);
    //     // Lcd7567.setCursor(0,font.yAdvance);
    //     Lcd7567.drawCircle(64,32,10,1);
    //     // Lcd7567.print("Xin Chao");

    //    int up=6;
    //   Lcd7567.setCursor(0, font.yAdvance-up);                    //Character display position. y=0-3, x=0-17
    //   Lcd7567.print("Xin Chao");
    //    Lcd7567.setCursor(0, font.yAdvance*2-up);                    //Character display position. y=0-3, x=0-17
    //   Lcd7567.print("Tot roi");
    //    Lcd7567.setCursor(0, font.yAdvance*3-up);                    //Character display position. y=0-3, x=0-17
    //   Lcd7567.print("Cuoi cung");
    //   Lcd7567.setCursor(0, font.yAdvance*4-up);                    //Character display position. y=0-3, x=0-17
    //   Lcd7567.print("Dong thu 4");
    //    Lcd7567.render();
    return;
}

void LCDThread::execute()
{

    // QX(4,3)


    TBT_THC(5,
        , ,
        TBT_IF( needUpdate == true,
            TBT_BLOCK(
                needUpdate = false;
                row = 0,
                updateText(),

                TBT_WHILE( row < LCD_HEIGHT / 8,
                    TBT_BLOCK(
                        col = 0,
                        TBT_WHILE( col < LCD_WIDTH, 
                            TBT_BLOCK(
                                Lcd7567.renderPartial(row, col);
                                col+=1,
                            )
                        ),
                        row += 1
                    )
                )

            ), 
        ),

        TBT_DELAY( 100),

        , ,
            // Lcd7567.draw_circle(105, 30, 15, DRAW_ALL, false, true),

    );

};