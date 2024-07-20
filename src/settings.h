#pragma once
#include "tbt_thread.h"
#include "events.h"
#include "pins.h"

using namespace std;
#define MAX_PWM_DUTY pow(2, PWM_RESOLUTION)

class Settings;
extern Settings *settings;
enum SPEED_TYPE {
    PWM,
    PFM
};
class Settings : public BaseThread
{
    static bool __handler(EventData *dt) { return settings->handler(dt); };
    bool handler(EventData *dt);
    void handleGear(EncoderData *dt);

public:
   
    int swing=0;
    int gear = 0;
    int maxGear = 9;
    bool inited = false;
    int pwmDuty();
    bool started = false;
    int minFreq=PFM_MIN_FREQUENCY;
    int maxFreq=PFM_MAX_FREQUENCY;
    // this will be calculate from gear, so dont touch it
    int pwmFrequency();
    SPEED_TYPE speedType=SPEED_TYPE::PFM;
    Settings();
    void loadSettings();
    void execute() override;
};
