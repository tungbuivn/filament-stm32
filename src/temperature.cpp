#include <Arduino.h>
#include "temperature.h"
#include "tbt_thread.h"
#include "mylcd.h"
#include <Adafruit_MAX31865.h>
#include "rtd100.h"

// use spi class

Adafruit_MAX31865 thermo = Adafruit_MAX31865(10);

// Use software SPI: CS, DI, DO, CLK
// Adafruit_MAX31865 thermo = Adafruit_MAX31865(10, 11, 12, 13);
// use hardware SPI, just pass in the CS pin
// Adafruit_MAX31865 thermo = Adafruit_MAX31865(10);

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF 430.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL 100.0

void createThread()
{
}
Temperature::Temperature()
{
  init = 0;

  // lcd.execute()
}
// TemperatureContext *tempContext=NULL;
void Temperature::execute()
{

  TBT_THC(
      5,
      , ,

      TBT_IF(false, TBT_BLOCK(
        // TBT_CREATE_CONTEXT(tempContext),
        
        TBT_EXECUTE_FUNC(TemperatureContext,tempContext, thermo.readRTD2,rtd=tempContext->rtd),  

                              temp = thermo.calculateTemperature(rtd, RNOMINAL, RREF),

                              fault = thermo.readFault(), TBT_IF(fault, TBT_BLOCK(

                                                                            if (fault & MAX31865_FAULT_HIGHTHRESH) {
                                                                              Serial.println("RTD High Threshold");
                                                                            } if (fault & MAX31865_FAULT_LOWTHRESH) {
                                                                              Serial.println("RTD Low Threshold");
                                                                            } if (fault & MAX31865_FAULT_REFINLOW) {
                                                                              Serial.println("REFIN- > 0.85 x Bias");
                                                                            } if (fault & MAX31865_FAULT_REFINHIGH) {
                                                                              Serial.println("REFIN- < 0.85 x Bias - FORCE- open");
                                                                            } if (fault & MAX31865_FAULT_RTDINLOW) {
                                                                              Serial.println("RTDIN- < 0.85 x Bias - FORCE- open");
                                                                            } if (fault & MAX31865_FAULT_OVUV) {
                                                                              Serial.println("Under/Over voltage");
                                                                            } thermo.clearFault();), )), ),

      // lbl2:
      // if ((micros() - time) > 50) goto lbl1,
      // goto lbl2,
      // lbl1:
      //   Serial.println();
      //   delay(1000);
      Serial.println(millis()),
      {
        // int t = millis() - time;
        mylcd.setTemp(millis());
      },

      // mylcd.setText(0,1*font.yAdvance,buf),

      // mylcd.
      // mylcd.setText(1,1,temp),

      // TBT_DELAY(10)
      // TBT_WAIT_THREAD(200, lcd)
  )
};