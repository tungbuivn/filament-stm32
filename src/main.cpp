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
#define SERIAL_RX_BUUFFER_SIZE 64
LCDThread mylcd;
Temperature temp;
LedBlink ledBlink;
SerialCmd mySerial;
// I2CScan i2cscan;
// HardwareSerial Serial1x(PA10, PA9);
void setup()
{
    // SERIAL_PORT_MONITOR
    //  Serial.setRx(PA12); // using pin name PY_n
    // Serial.setTx(PA11); // using pin number PYn
    Serial.begin(9600);
    
    
   delay(2000);
  
    // Serial.dtr(false);
	// while(Serial1x);
    // while(!Serial.available()) {
    //     delay(100);
    // }
    uint32_t tm=millis();
    wait_more:
//    Serial.println("hello");
    if (!Serial.availableForWrite()) {
        // Serial.clearWriteError();
        goto wait_more;
    }
     Serial.println("hello");
    Serial.println(millis()-tm);

    ledBlink.init();
    mylcd.init();
};

void loop()
{
    mylcd.execute();
    temp.execute();
    ledBlink.execute();
    mySerial.execute();
    // i2cscan.execute();
    // return;
    // delay(1);

}