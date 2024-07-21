// #include "I2C_eeprom.h"
#include "settings.h"
#include "pins.h"
#include "events.h"
#include "encode2.h"
#include "eventData.h"
#include "UI/manager.h"
#include "Wire.h"

#define EEPROM_ADDRESS 0x50
// I2C_eeprom ee(0x50);
Settings::Settings()
{
    Wire.begin();

    Wire.beginTransmission(EEPROM_ADDRESS);
    eepromError = Wire.endTransmission();
    inited = false;

    // eventSystem.addListener(EventType::SETTINGS_UPDATE_PWM,Settings::handler);
    eventSystem.addListener(EventType::SETTINGS_UPDATE_GEAR, Settings::__handler);
    eventSystem.addListener(EventType::BUTTON_TRIGGER, Settings::__handler);
    eventSystem.addListener(EventType::ENCODER_ROTATE, Settings::__handler);
    eventSystem.addListener(EventType::ENCODER_CLICK, Settings::__handler);
    eventSystem.addListener(EventType::TEMPERATURE_CHANGE, Settings::__handler);
}
void Settings::handleGear(EncoderData *dt)
{
    if (dt->dir == ENCODER_DIRECTION::RIGHT)
    {
        gear += 1;
        if (gear > maxGear)
        {
            gear = maxGear;
        }
    }
    else if (dt->dir == ENCODER_DIRECTION::LEFT)
    {
        gear -= 1;
        if (gear < 0)
        {
            gear = 0;
        }
    }

    GearData gdt;
    gdt.gear = gear;
    eventSystem.dispatchMessage(EventType::GEAR_UPDATED, &gdt);

    // calculate pwm & update
    // calculate freq

    MotorPwmData mt;
    mt.pwm = pwmDuty();
    debug_printf("setting->send PWM_UPDATE\n");
    eventSystem.dispatchMessage(EventType::PWM_UPDATED, &mt);
}
int Settings::pwmFrequency()
{
    int freq = 0;
    if (settings->gear > settings->maxGear)
    {
        settings->gear = settings->maxGear;
        eventSystem.dispatchMessage(EventType::GEAR_UPDATED, NULL);
    }
    if (settings->speedType == SPEED_TYPE::PFM)
    {
        freq = settings->minFreq + (settings->gear * (settings->maxFreq - settings->minFreq) / settings->maxGear);
    }
    else
    {
        freq = settings->maxFreq;
    }
    return freq;
}
int Settings::pwmDuty()
{
    int duty = 0;
    if (settings->gear > settings->maxGear)
    {
        settings->gear = settings->maxGear;
        eventSystem.dispatchMessage(EventType::GEAR_UPDATED, NULL);
    }
    if (settings->speedType == SPEED_TYPE::PFM)
    {
        if (gear == 0)
            duty = 0;
        else
            duty = MAX_PWM_DUTY / 2;
    }
    else
    {

        duty = (gear * MAX_PWM_DUTY) / maxGear;
        if (duty >= MAX_PWM_DUTY - 1)
        {
            duty = MAX_PWM_DUTY - 1;
        }
    }

    return duty;
}
void Settings::resetSleep()
{
    sleepRemain = sleepTime;
    analogWrite(LCD_LED, lcdBrightness);
}
bool Settings::handler(EventData *adt)
{
    switch (adt->type)
    {
    case EventType::SETTINGS_UPDATE_GEAR:
        handleGear((EncoderData *)adt);
        break;
    case EventType::BUTTON_TRIGGER:
    {
        resetSleep();
        auto abtn = (ButtonState *)adt;
        if (abtn->btn == BUTTON_STATE::BTN_FAN)
        {
            started = !started;
            OnOffData onOff;
            onOff.state = started;
            eventSystem.dispatchMessage(EventType::ON_OFF_UPDATED, &onOff);
            // eventSystem.dispatchMessage(EventType::GEAR_UPDATED, NULL);
        }
        else
        {
            // swing button press
            swing = !swing;
            SwingData sw;
            sw.state = swing;
            eventSystem.dispatchMessage(EventType::SWING_UPDATED, &sw);
        }
    }

    break;
    case ENCODER_ROTATE:
    case ENCODER_CLICK:
        resetSleep();
        break;
    case TEMPERATURE_CHANGE:
        auto ntemp=((TemperatureData *)adt)->temperature;
        if (ntemp!=temperature) {
            temperature=ntemp;
            eventSystem.dispatchMessage(EventType::GEAR_UPDATED,NULL);
        }
        // temperature = ((TemperatureData *)adt)->temperature;
        break;
    }
    return false;
}
void Settings::writeByte(unsigned int add, uint8_t data)
{
    Wire.beginTransmission(EEPROM_ADDRESS);
    Wire.write((int)(add >> 8));   // left-part of pointer address
    Wire.write((int)(add & 0xFF)); // and the right
    Wire.write(data);
    Wire.endTransmission();
    delay(5); // small delay for eeprom to save data
}
uint8_t Settings::readByte(unsigned int add)
{
    Wire.beginTransmission(EEPROM_ADDRESS); // I2C address
    Wire.write((int)(add >> 8));            // bit shift for high byte of pointer address
    Wire.write((int)(add & 0xFF));          // mask for the low byte
    Wire.endTransmission();
    Wire.requestFrom(EEPROM_ADDRESS, 1);
    return Wire.read();
}
void Settings::initData()
{
    int buf[] = {
        speedType,
        autoGear,
        gear,
        maxGear,
        lcdBrightness,
        lcdMaxBrightness,
        minTemperature,
        maxTemperature,
        sleepTime,
        powerOff};
    int len = sizeof(buf) / sizeof(int);
    for (int i = 0; i < len; i++)
    {
        storage[i] = buf[i];
    }
}
void Settings::saveSetting()
{
    initData();
    uint8_t *data = (uint8_t *)&storage;
    int len = sizeof(storage);
    for (int i = 0; i < len; i++)
    {
        auto b=readByte(EEPROM_OFFSET+i);
        if (b!=data[i]) {
            writeByte(EEPROM_OFFSET + i, data[i]);
        }
        
    }
}
void Settings::loadSettings()
{
    // return;
    uint8_t *data = (uint8_t *)&storage;
    int len = sizeof(storage);
    for (int i = 0; i < len; i++)
    {
        data[i]=readByte(EEPROM_OFFSET+i);
    }
    int i=0;
    speedType=(SPEED_TYPE)storage[i++];
    autoGear=(EN_FAN_AUTO)storage[i++];
    gear=storage[i++];
    maxGear=storage[i++];
    lcdBrightness=storage[i++];
    lcdMaxBrightness=storage[i++];
    minTemperature=storage[i++];
    maxTemperature=storage[i++];
    sleepTime=storage[i++];
    powerOff=storage[i++];

    powerOffRemain=powerOff;


}
void Settings::handleAutoPowerOff(ThreadData *data)
{
   
    AUTO_THC(data, 
        TBT_DELAY(1000), 
        if (!started) {powerOffRemain=powerOff;},
        if (started && (powerOffRemain > 0)) {
            powerOffRemain -= 1;
            if (powerOffRemain <= 0)
            {
                powerOffRemain = 0;
                started=false;
                eventSystem.dispatchMessage(EventType::ON_OFF_UPDATED, NULL);
                // analogWrite(LCD_LED, 0);
            } 
        }, 
        if (powerOffRemain < 0) powerOffRemain = 0, 
    )
}
void Settings::handleSleep(ThreadData *data)
{
   
    AUTO_THC(data, 
        TBT_DELAY(1000), 
        if (sleepRemain > 0) {
            sleepRemain -= 1;
            if (sleepRemain <= 0)
            {
                sleepRemain = 0;
                analogWrite(LCD_LED, 0);
            } 
        }, 
        if (sleepRemain < 0) sleepRemain = 0, 
    )
}
void Settings::handleAutoSpeed(ThreadData *data)
{
    // static int lastTemp=0;
    AUTO_THC(data,
             TBT_IF_TRUE(autoGear == EN_FAN_AUTO::ON,

                         if (started && (minTemperature <= maxTemperature)) {
                             bool trigger = false;
                             if (temperature <= minTemperature)
                             {
                                 // turn off
                                 if (gear != 0)
                                 {
                                     gear = 0;
                                     trigger = true;
                                 }
                             }
                             if (temperature >= maxTemperature)
                             {
                                 if (gear != maxGear)
                                 {
                                     trigger = true;
                                     gear = maxGear;
                                 }
                             }
                             if (!trigger)
                             {
                                 int dist = maxTemperature - minTemperature;
                                 if (dist != 0)
                                 {

                                     int dist2 = temperature - minTemperature;
                                     int newGear = dist2 * maxGear / dist;

                                     if (newGear != gear)
                                     {
                                         gear = newGear;
                                        trigger=true;
                                     }
                                 }
                             }
                             if (trigger) {
                                debug_printf("auto gear %d\n", gear);
                                eventSystem.dispatchMessage(EventType::GEAR_UPDATED, NULL);
                             } }, TBT_DELAY(500), ))
}
void Settings::execute()
{
    static ThreadData sleepTh;
    static ThreadData autoSpeed;
    static ThreadData autoOff;
    EventEmpty ev;
    // debug_printf("setting execute!\n");
    TBT_THC(5, if (!inited) {
        inited=true;
        debug_printf("Setting init !\n");
        loadSettings();
        resetSleep();
        man->init();
        debug_printf("Setting loaded !\n");
        eventSystem.dispatchMessage(EventType::RENDER,&ev); }, 
        handleSleep(&sleepTh), 
        handleAutoSpeed(&autoSpeed),
        handleAutoPowerOff(&autoOff),

    )
}