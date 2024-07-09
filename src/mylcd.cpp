#include "mylcd.h"
#include "tbt_thread.h"
#include <Arduino.h>
// #include <U8g2lib.h>
#include <Wire.h>
// #include <lcd.h>
// #include "lcd/lcd_st7567s.h"

#define LCD_SCL PB6
#define LCD_SDA PB7

// 
// U8G2_ST7567_ENH_DG128064I_F_HW_I2C   u8g2(U8G2_R0,U8X8_PIN_NONE,SCL,SDA);

// ST7567_128
//create an lcd object.
// lcd_st7567s Lcd7567;
// lcd  lcd;
LCDThread::LCDThread(EncoderThread *enc,EncoderClick *clickEnc) : BaseThread(){

    enc->onChange(LCDThread::onEncoderChange);
    clickEnc->onClick(LCDThread::onEncoderClick);

};
void LCDThread::onEncoderClick() {

}
void LCDThread::onEncoderChange(int dir) {

}
    
void LCDThread::execute(){

    TBT_THC(5,
    ,,
    
    
       
    )
};