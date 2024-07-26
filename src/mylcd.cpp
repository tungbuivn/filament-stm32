#include "mylcd.h"
#include "tbt_thread.h"
#include <Arduino.h>
// #include <U8g2lib.h>
#include <Wire.h>

#include <SPI.h>
#include "pins.h"
#include "events.h"
#include <string>
#include "settings.h"
// #include "UI/sfui9.h"
// #include "NotoSansBold36.h"

// The font names are arrays references, thus must NOT be in quotes ""
// #define AA_SFUI sfui9

using namespace std;

// For the breakout board, you can use any 2 or 3 pins.
// These pins will also work for the 1.8" TFT shield.
//   #define TFT_CS        10
//   #define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
//   #define TFT_DC         8

// OPTION 1 (recommended) is to use the HARDWARE SPI pins, which are unique
// to each board and not reassignable. For Arduino Uno: MOSI = pin 11 and
// SCLK = pin 13. This is the fastest mode of operation and is required if
// using the breakout board's microSD card.

// Adafruit_ST7789 tft = Adafruit_ST7789(&SPI,LCD_CS, LCD_DC,  LCD_RST);
// #include "lcd/lcd_st7567s.h"

// #define LCD_SCL PB6
// #define LCD_SDA PB7

//
// U8G2_ST7567_ENH_DG128064I_F_HW_I2C   u8g2(U8G2_R0,U8X8_PIN_NONE,SCL,SDA);

// ST7567_128
// create an lcd object.
// lcd_st7567s Lcd7567;
// lcd  lcd;
// LCDThread *meLCD=NULL;
void LCDThread::initTFT()
{

  // analogWrite(LCD_LED, MAX_PWM_DUTY - 1);

  tft = new TFT_eSPI();
  tft->begin();
  tft->setRotation(2);
  tft->fillScreen(TFT_BLACK);
  
}
LCDThread::LCDThread() : BaseThread()
{

  pinMode(PIN_SPI_SS, OUTPUT);
  pinMode(PIN_SPI_MISO, INPUT_PULLUP);
  pinMode(PIN_SPI_MOSI, OUTPUT);
  pinMode(PIN_SPI_SCK, OUTPUT);
  pinMode(TFT_DC, OUTPUT);
  pinMode(TFT_RST, OUTPUT);
  pinMode(LCD_LED, OUTPUT);

  initTFT();

};

// void LCDThread::setPwmText(const char *text) {
//   if (!mylcd) return;
//   debug_printf("lcd update pwm %s\n",text);
//   auto tft=mylcd->tft;
//   tft->fillRect(60,72,120,80,TFT_RED);

//   tft->setFreeFont(FSB40pt);
//   tft->setTextDatum(MC_DATUM);
//   tft->setTextColor(TFT_GREEN);
//   // std::string s = std::to_string(PwmData->pwm);
//   // tft->set(TFT_BLUE);
//   // tft->setTextSize(24);
//   tft->drawString(text,120,160-40-5,1);
// }
// bool LCDThread::OffPwm(EventData *data) {
//    setPwmText("--");
//    return false;
// }
// bool LCDThread::UpdatePwm(EventData *data) {
//   if (!mylcd) return false;

//   auto pwmData=(MotorPwmData*)data;

//   char buf[12];
//   ltoa(pwmData->pwm,buf,10);

//   setPwmText(buf);
//   return false;
// }
// bool LCDThread::onEncoderChange(EventData *data) {

//   auto ndt=(EncoderData *)data;
//   debug_printf("encode change %d\n",ndt->dir);
//   return false;
// }

void LCDThread::execute() {
  //
  //   delay(500);
  //   tft.invertDisplay(false);
  //   delay(500);
  TBT_THC(5,
          , ,
          // tft.invertDisplay(true),
          // TBT_DELAY(500),
          //  tft.invertDisplay(false),
          //  TBT_DELAY(500)

          )
};