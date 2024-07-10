#include <Wire.h>
#include <LiquidCrystal_Software_I2C.h>
#include "dbglcd.h"
#include <Arduino.h>
// #include <Wire.h>
#include <pins.h>

// TwoWire Wire2(PB3, PB10);
LCDTBT::LCDTBT() : LiquidCrystal_I2C(0x27, 16, 2,EXP_SDA2,EXP_SCL2)
{
    // TwoWire Wire2(PB3, PB10);
    init(); // initialize the lcd
    backlight();
    // print("Hello, world!");
    // print("Hello world");
    // int value = 0x03;

    // write4bits(0x03);
    // pulseEnable;
    // // delayMicroseconds(9500); // wait min 4.1ms

    // // // second try
    // write4bits(0x03);
    // delayMicroseconds(9500); // wait min 4.1ms

    // // // third go!
    // write4bits(0x03);
    // delayMicroseconds(850);

    // // // finally, set to 4-bit interface
    // write4bits(0x02);
    // init(1, rs, 255, enable, d4, d5, d6, d7, 0, 0, 0, 0);
    // delay(300);
    // init(1, rs, 255, enable, d4, d5, d6, d7, 0, 0, 0, 0);
    // delay(300);
    // init(1, rs, 255, enable, d4, d5, d6, d7, 0, 0, 0, 0);
    // delay(300);
    //        begin(16, 2);
    // print('A');
    // digitalWrite(rs, LOW);
    // digitalWrite(rs, HIGH);

    // digitalWrite(enable, LOW);
    // digitalWrite(enable, HIGH);

    // digitalWrite(d4, LOW);
    // digitalWrite(d4, HIGH);

    // digitalWrite(d5, LOW);
    // digitalWrite(d5, HIGH);
    // digitalWrite(d6, LOW);
    // digitalWrite(d6, HIGH);
    // digitalWrite(d7, LOW);
    // digitalWrite(d7, HIGH);
}

void LCDTBT::startup()
{
    // clear();
    // home();
    // begin(16, 2);

    // home = ahome;
}
// void lcdInit()
// {

//     lcd.begin(16, 2);
//     lcd.setCursor(10, 1);
//     lcd.print("xyz");
// }