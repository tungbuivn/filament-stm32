#include "mylcd.h"
#include "tbt_thread.h"
#include <Arduino.h>
// #include <U8g2lib.h>
#include <Wire.h>
// #include <lcd.h>
#include "lcd/lcd_st7567s.h"

#define LCD_SCL PB6
#define LCD_SDA PB7

// 
// U8G2_ST7567_ENH_DG128064I_F_HW_I2C   u8g2(U8G2_R0,U8X8_PIN_NONE,SCL,SDA);

// ST7567_128
//create an lcd object.
lcd_st7567s Lcd7567;
// lcd  lcd;
LCDThread::LCDThread() : BaseThread(){

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
    c->text = new char[s.size()]; //memory allocated
    strcpy(c->text, s.c_str());
   
    c->x = x;
    c->y = y;
    
    // Serial.println("=====");
    // Serial.println(c->text);
    // c->text = text;
    data.push(c);
}
    
void LCDThread::updateText() {
    if (data.size()>0) {
       
        TextQueueData *inf = data.front();
        // Serial.print("Update text lcd: ");
        // Serial.println(inf->text);
         Lcd7567.Cursor(inf->x, inf->y);                    //Character display position. y=0-3, x=0-17
  Lcd7567.Display(inf->text); 
        // Lcd7567.
        data.pop();
        delete[] inf->text;
        delete inf;
   
    }
   
}
void LCDThread::initLcd() {
    //   Wire.setSDA(SDA);
    // Wire.setSCL(SCL);
    Lcd7567.Init();
    Lcd7567.testPixel(2);

     Lcd7567.Clear(true);
 
/**/  
  Lcd7567.Cursor(0, 7);                    //Character display position. y=0-3, x=0-17
  Lcd7567.Display("Xin chao");  
    return;
    
  for(int a=0; a<64; a++){
  Lcd7567.DisplayPixel(a,a);              //display one pixel. X=0-31, Y=0-127
  delay(5);
  }
  for(int a=0; a<64; a++){
  Lcd7567.ClearPixel(a,a);                //Does not display a pixel. X=0-31, Y=0-127
  delay(5);
  }

  Lcd7567.Clear(true);
  for(int a=0; a<64; a++){
  Lcd7567.ClearPixel(a,a);                //Does not display a pixel. X=0-31, Y=0-127
  delay(5);
  }
  delay(5000);

  Lcd7567.Clear(false);
  for(int a=0; a<128; a++){
  Lcd7567.DisplayPixel(a,0);              //display one pixel. X=0-31, Y=0-127
  Lcd7567.DisplayPixel(a,63);              //display one pixel. X=0-31, Y=0-127
  }
  for(int a=0; a<64; a++){
  Lcd7567.DisplayPixel(0, a);              //display one pixel. X=0-31, Y=0-127
  Lcd7567.DisplayPixel(127,a);              //display one pixel. X=0-31, Y=0-127
  Lcd7567.DisplayPixel(4,a);
  }
  Lcd7567.DrawLine(5, 5, 125, 60, false);
  Lcd7567.DrawLine(125, 5, 5, 60, false);
  Lcd7567.DrawLine(53, 31, 73, 31, false);
  Lcd7567.DrawLine(63, 20, 63, 40, false);

  Lcd7567.draw_circle(20, 30, 10, DRAW_ALL, false, false);
  Lcd7567.draw_circle(20, 30, 15, DRAW_ALL, false, false);

  Lcd7567.draw_circle(105, 30, 15, DRAW_ALL, false, true);

  delay(5000);

  Lcd7567.Clear(false);
  Lcd7567.DrawLine(53, 31, 73, 31, false);
  Lcd7567.DrawLine(63, 20, 63, 40, false);
  Lcd7567.draw_circle(90, 30, 10, DRAW_ALL, false, false);
  Lcd7567.draw_circle(30, 30, 10, DRAW_ALL, false, true);
  delay(5000);

  Lcd7567.Clear(true);
  Lcd7567.DrawLine(53, 31, 73, 31, true);
  Lcd7567.DrawLine(63, 20, 63, 40, true);
  Lcd7567.draw_circle(90, 30, 10, DRAW_ALL, true, false);
  Lcd7567.draw_circle(30, 30, 10, DRAW_ALL, true, true);
  delay(5000);

/**/  
  Lcd7567.Cursor(7, 0);                    //Character display position. y=0-3, x=0-17
  Lcd7567.Display("KEYES");               //Maximun 18 characters.
  Lcd7567.Cursor(0, 1);
  Lcd7567.Display("ABCDEFGHIJKLMNOPQR");
  Lcd7567.Cursor(0, 2);
  Lcd7567.Display("123456789+-*/<>=$@");
  Lcd7567.Cursor(0, 3);
  Lcd7567.Display("%^&(){}:;'|?,.~\\[]");
  Lcd7567.Cursor(0, 4);
  Lcd7567.Display("ABCDEFGHIJKLMNOPQR");
  Lcd7567.Cursor(0, 5);
  Lcd7567.Display("123456789+-*/<>=$@");
  Lcd7567.Cursor(0, 6);
  Lcd7567.Display("%^&(){}:;'|?,.~\\[]");
  Lcd7567.Cursor(0, 7);
  Lcd7567.Display("ABCDEFGHIJKLMNOPQR");
  delay(5000);
  Lcd7567.Clear(false);                        //All pixels turn off.
  
  Lcd7567.DisplayPicture();               //Displays the image data for the picture.c file
  delay(5000);
}
void LCDThread::execute(){

    TBT_THC(5,
    ,,
    if (init==0) {
        init=1;
        initLcd();
    },
    updateText(),
    // Lcd7567.draw_circle(105, 30, 15, DRAW_ALL, false, true),
    
       
    )
};