#include <Arduino.h>
#include "temperature.h"
#include "tbt_thread.h"
#include "mylcd.h"
#include <Adafruit_MAX31865.h>

// use spi class

Adafruit_MAX31865 thermo = Adafruit_MAX31865(10);

// Use software SPI: CS, DI, DO, CLK
// Adafruit_MAX31865 thermo = Adafruit_MAX31865(10, 11, 12, 13);
// use hardware SPI, just pass in the CS pin
//Adafruit_MAX31865 thermo = Adafruit_MAX31865(10);

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      430.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0

void createThread() {

}
Temperature::Temperature()
{
    init=0;
    
    
// lcd.execute()
}


void Temperature::execute(){
    if (init==0) {
            init=1;
            // SPI.setMISO();
            // SPI.setMOSI();
            // SPI.setSCLK();
    };
    TBT_THC(4,
        ,,
        rtd = thermo.readRTD(),

  Serial.print("RTD value: ");
   Serial.println(rtd),
  ratio = rtd,
  ratio /= 32768,
  Serial.print("Ratio = "); Serial.println(ratio,8),

  Serial.print("Resistance = "); Serial.println(RREF*ratio,8),
  temp=thermo.temperature(RNOMINAL, RREF),
  Serial.print("Temperature = "); //Serial.println(temp),

  // Check and print any faults
  fault = thermo.readFault(),
  if (fault) {
    Serial.print("Fault 0x"); Serial.println(fault, HEX);
    if (fault & MAX31865_FAULT_HIGHTHRESH) {
      Serial.println("RTD High Threshold"); 
    }
    if (fault & MAX31865_FAULT_LOWTHRESH) {
      Serial.println("RTD Low Threshold"); 
    }
    if (fault & MAX31865_FAULT_REFINLOW) {
      Serial.println("REFIN- > 0.85 x Bias"); 
    }
    if (fault & MAX31865_FAULT_REFINHIGH) {
      Serial.println("REFIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault & MAX31865_FAULT_RTDINLOW) {
      Serial.println("RTDIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault & MAX31865_FAULT_OVUV) {
      Serial.println("Under/Over voltage"); 
    }
    thermo.clearFault();
  },
//   Serial.println();
//   delay(1000);
        // Serial.println("setup text"),
        // mylcd.setText(0,2,"Temperature"),
        // mylcd.setText(1,1,temp),
          
            TBT_DELAY(100,500)
            // TBT_WAIT_THREAD(200, lcd)
    )

};