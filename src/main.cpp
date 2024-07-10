#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_BusIO_Register.h>
// #include "mylcd.h"
#include <USBSerial.h>
// #include "temperature.h"
#include "led-blink.h"
#include "serialcmd.h"
#include "pwm_ctrl.h"
#include "encode2.h"
#include "buzzer.h"
// #include "i2c-scan.h"
// #include <Wire.h>
// #define SERIAL_PORT_MONITOR     Serial
//   #define SERIAL_PORT_HARDWARE    Serial
// HardwareSerial Serial1(PA10, PA9);
// LCDThread *mylcd;
// Temperature temp;
LedBlink *ledBlink;
SerialCmd mySerial;
PWMControl *pwmCtrl;
EncoderThread *enc;
EncoderClick *clickEnc;
Buzzer *buz;

// I2CScan i2cscan;
// HardwareSerial Serial1x(PA10, PA9);
void setup()
{
   
    Serial.begin(9600);

    enc=new EncoderThread();
    pwmCtrl=new PWMControl();
    clickEnc=new EncoderClick();
    // mylcd=new LCDThread(enc,clickEnc);
    ledBlink=new LedBlink();
    buz=new Buzzer();
   
};

void loop()
{
    //  analogWrite(PWM_BLDC, 95 * 255 / 100);
    pwmCtrl->execute();
    enc->execute();
    clickEnc->execute();

    // analogWriteResolution

    // delay(5000);
    // mylcd.execute();
    // temp.execute();
    ledBlink->execute();
    mySerial.execute();
    // i2cscan.execute();
    // return;
}
void a()
{
   
}