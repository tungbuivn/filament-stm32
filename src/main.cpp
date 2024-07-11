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
EncoderThread *rotaryEncoder;
EncoderClick *encoderButton;
Buzzer *buz;

// I2CScan i2cscan;
// HardwareSerial Serial1x(PA10, PA9);
void setup()
{
   
    Serial.begin(9600);

    rotaryEncoder=new EncoderThread();
    pwmCtrl=new PWMControl();
    encoderButton=new EncoderClick();
    // mylcd=new LCDThread(enc,encoderButton);
    ledBlink=new LedBlink();
    buz=new Buzzer();
   
};

void loop()
{
    //  PWM control
    pwmCtrl->execute();
    rotaryEncoder->execute();
    encoderButton->execute();

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