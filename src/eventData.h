#pragma once
#include "events.h"
#include "encode2.h"
#include <string>
using namespace std;
enum EventType {
    NONE,
    SERIAL_CMD,
    ENCODER_CLICK,
    ENCODER_ROTATE,
    TEMPERATURE_CHANGE,
    BUTTON_TRIGGER,
    SAVE_SETTINGS,
    GOTO_PAGE,
    RENDER,
    // trigger from home page
    SETTINGS_UPDATE_PWM,
    SETTINGS_UPDATE_GEAR,

    // trigger when pwm value changed
    PWM_UPDATED,
    GEAR_UPDATED,
    ON_OFF_UPDATED,
    SWING_UPDATED,
    TEMPERATURE_UPDATED,
    // MOTOR_UPDATE_PWM,
    // TFT_UPDATE_PWM=MOTOR_UPDATE_PWM,
    LCD_OFF_PWM
};
class EventData {

public:
    EventType type;
    virtual ~EventData();
    virtual EventData* clone()=0;
};

class EventEmpty: public EventData {

public:
   
    EventEmpty(){}
    EventEmpty(EventEmpty *aobj) {type=aobj->type;}
    EventData* clone(){return new EventEmpty(this);}
   
};

class MotorPwmData : public EventData {
public:
    int pwm;
    MotorPwmData(){}
    MotorPwmData(MotorPwmData *aobj) {pwm=aobj->pwm;type=aobj->type;}
    EventData* clone(){return new MotorPwmData(this);}
};


class EncoderClickData:public EventData {
public:
 
    EncoderClickData(){}
    EncoderClickData(EncoderClickData *aobj) {type=aobj->type;}
    EncoderClickData* clone(){return new EncoderClickData(this);}
};

enum ENCODER_DIRECTION {
    NONE_DIRECTION,
    LEFT,
    RIGHT
};
class EncoderData:public EventData {
public:
    ENCODER_DIRECTION dir;    
    EncoderData(){}
    EncoderData(EncoderData *aobj) {dir=aobj->dir;type=aobj->type;}
    EventData* clone(){return new EncoderData(this);}
};

enum BUTTON_STATE {
    BTN_NONE,
    BTN_FAN,
    BTN_SWING
};
class ButtonState : public EventData {
public:
    BUTTON_STATE btn;
    ButtonState(){}
    ButtonState(ButtonState *aobj) {btn=aobj->btn;type=aobj->type;}
    EventData* clone(){return new ButtonState(this);}

};



class TemperatureData: public EventData {
public:
    int temperature;
    TemperatureData(){}
    TemperatureData(TemperatureData *aobj) {temperature=aobj->temperature;type=aobj->type;}
    EventData* clone(){return new TemperatureData(this);}
};

class SerialData : public EventData {
public:
    string data;
    SerialData(){}
    SerialData(SerialData *aobj) {data=aobj->data;type=aobj->type;}
    EventData* clone(){return new SerialData(this);}
};

class PageJump:public EventData {
public:
    int page;
    PageJump(){}
    PageJump(PageJump *aobj) {page=aobj->page;type=aobj->type;}
    EventData* clone(){return new PageJump(this);}
};

class GearData:public EventData {
public:
    int gear;
    GearData(){}
   
    GearData(GearData *aobj) {gear=aobj->gear;type=aobj->type;}
    EventData* clone(){return new GearData(this);}
};

class OnOffData:public EventData {
public:
    int state;
    OnOffData(){}
   
    OnOffData(OnOffData *aobj) {state=aobj->state;type=aobj->type;}
    EventData* clone(){return new OnOffData(this);}
};
class SwingData:public EventData {
public:
    int state;
    SwingData(){}
   
    SwingData(SwingData *aobj) {state=aobj->state;type=aobj->type;}
    EventData* clone(){return new SwingData(this);}
};