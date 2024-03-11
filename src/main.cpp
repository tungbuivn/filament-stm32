#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_BusIO_Register.h>
#include "mylcd.h"
#include "temperature.h"
#include "led-blink.h"
#include "serialcmd.h"
// #include "i2c-scan.h"
// #include <Wire.h>
// #define SERIAL_PORT_MONITOR     Serial
//   #define SERIAL_PORT_HARDWARE    Serial

LCDThread mylcd;
Temperature temp;
LedBlink ledBlink;
SerialCmd mySerial;
// I2CScan i2cscan;
// HardwareSerial Serial1x(PA10, PA9);
void setup()
{
    
    //  Serial.setRx(PA10); // using pin name PY_n
    // Serial.setTx(PA9); // using pin number PYn
    Serial.begin(115200);
    
   
    // Serial.dtr(false);
	// while(Serial1x);
    // while(!Serial.available());
    pinMode(LED_BUILTIN,OUTPUT);
};

void loop()
{
    mylcd.execute();
    temp.execute();
    ledBlink.execute();
    mySerial.execute();
    // i2cscan.execute();
    return;

}