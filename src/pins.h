#pragma once
#include <Arduino.h>




// bldc motor 
// pwm signal to control motor
#define PWM_BLDC    PA2


// UI
// on off button
#define ONOFF       PA12
#define SWING       PA11
// encoder
#define encA        PB4
#define encB        PB5
#define encClick    PB8
// lcd
#define LCD_CS      PIN_SPI_SS
#define LCD_MISO    PIN_SPI_MISO
#define LCD_MOSI    PIN_SPI_MOSI
#define LCD_SCK     PIN_SPI_SCK

// buzzer
#define BUZZER      PA3

// eeprom

// temp
#define TEMPERATURE PA1

//infrated led

// step motor swing