#include "I2C_eeprom.h"
#include "settings.h"
#include "pins.h"
#include "events.h"
#include "encode2.h"
#include "eventData.h"

I2C_eeprom ee(0x50);
Settings::Settings()
{
    Wire.begin();

    ee.begin();
    if (!ee.isConnected())
    {
        debug_printf("ERROR: Can't find eeprom\n");
    }
    debug_printf("isConnected: %d\n", ee.isConnected());
    inited = false;
   
    // eventSystem.addListener(EventType::SETTINGS_UPDATE_PWM,Settings::handler);
    eventSystem.addListener(EventType::SETTINGS_UPDATE_GEAR, Settings::__handler);
    eventSystem.addListener(EventType::BUTTON_TRIGGER, Settings::__handler);
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
    else
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
int Settings::pwmFrequency() {
    int freq=0;
    if (settings->speedType==SPEED_TYPE::PFM) {
        freq = settings->minFreq + (settings->gear * (settings->maxFreq - settings->minFreq) / settings->maxGear);
    } else {
        freq=settings->maxFreq;
    }
    return freq;
}
int Settings::pwmDuty() {
    int duty=0;
    if (settings->speedType==SPEED_TYPE::PFM){
        if (gear==0) 
            duty=0; 
        else
            duty=MAX_PWM_DUTY/2;
    } else {
        
        duty=(gear*MAX_PWM_DUTY)/maxGear;
        if (duty>=MAX_PWM_DUTY-1) {
            duty=MAX_PWM_DUTY-1;
        }
    }
   
    return duty;
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
            auto abtn=(ButtonState*)adt;
            if (abtn->btn==BUTTON_STATE::BTN_FAN) {
                started=!started;
                OnOffData onOff;
                onOff.state=started;
                eventSystem.dispatchMessage(EventType::ON_OFF_UPDATED, &onOff);
            } else {
                // swing button press
                swing=!swing;
                SwingData sw;
                sw.state=swing;
                eventSystem.dispatchMessage(EventType::SWING_UPDATED, &sw);
            }
        }
   
        break;
    }
    return false;
}

void Settings::loadSettings()
{
    const int len = 20;
    uint8_t buf[len];
    ee.readBlock(EEPROM_OFFSET, buf, len);
    // get max gear from settings
    maxGear = 9;

    // get saved value pwm duty
    // MotorPwmData mt;
    // // pwmDuty = 0;
    // mt.pwm = pwmDuty();
    // eventSystem.dispatchMessage(EventType::PWM_UPDATED,&mt);
}
void Settings::execute()
{
    EventEmpty ev;
    // debug_printf("setting execute!\n");
    TBT_THC(5, if (!inited) {
        inited=true;
        debug_printf("Setting init !\n");
        loadSettings();
        debug_printf("Setting loaded !\n");
        eventSystem.dispatchMessage(EventType::RENDER,&ev); },

    )
}