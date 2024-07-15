#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_BusIO_Register.h>
#include "mylcd.h"
#include <USBSerial.h>
#include "led-blink.h"
#include "serialcmd.h"
#include "pwm_ctrl.h"
#include "encode2.h"
#include "buzzer.h"
#include "temperature.h"
#include "events.h"
#include "UI/manager.h"

Events eventSystem;

vector<BaseThread*> listThread;
int len;

void setup()
{

    Serial.begin(115200);
    delay(2000);
    listThread.assign({
        new EncoderRotate(),
        new EncoderClick(),
        new PWMControl(),
        new Temperature(),
        new LCDThread(),
        new LedBlink(),
        new Buzzer(),
        new SerialCmd(),
        new ManagerPage()
    });
    len = listThread.size();
};

void loop()
{
    for (int i = 0; i < len; i++)
        listThread.at(i)->execute();
}