#pragma once
#include <Arduino.h>




// bldc motor 
// pwm signal to control motor
#define PWM_BLDC                PA2


// UI
// on off button
#define ONOFF                   PA10    
#define SWING                   PA9     

// PA12  // DP
// PA11  // DM
// encoder
#define PIN_ENCODER_A           PB4
#define PIN_ENCODER_B           PB5
#define PIN_ENCODER_CLICK       PB8


// lcd
#ifndef LCD_READ_ID
  #define LCD_READ_ID 0x04   // Read display identification information (0xD3 on ILI9341)
#endif
#ifndef LCD_READ_ID4
  #define LCD_READ_ID4 0xD3   // Read display identification information (0xD3 on ILI9341)
#endif



#define LCD_CS                  PIN_SPI_SS
#define LCD_MISO                PIN_SPI_MISO
#define LCD_MOSI                PIN_SPI_MOSI
#define LCD_SCK                 PIN_SPI_SCK

#define LCD_DC                  PB1
#define LCD_RST                 PB2
#define LCD_LED                 PB0


// i2c 2
#define EXP_SDA2                PB3
#define EXP_SCL2                PB10

// buzzer
#define BUZZER                  PA3

// eeprom

// temp
#define TEMPERATURE             PA1
// resistor value which connected in series to NTC used to measure temp
#define RESITOR_MEASURED        4700 // resistor 4k7

//infrated led

// step motor swing