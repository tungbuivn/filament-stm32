#include <Arduino.h>
#include "temperature.h"
#include "tbt_thread.h"
#include "mylcd.h"
#include "pins.h"
#include "macro.h"
#include "ntc.h"
#include "events.h"

// #define MAX_TEMP_ADC 4095

const int MAX_TEMP_ADC=(int)(pow(2,ADC_RESOLUTION)-1);

Temperature::Temperature()
{
// lcd.execute()
    pinMode(TEMPERATURE,INPUT);
    analogReadResolution(12);
}


void Temperature::execute(){

    
    static int temp=0;
    static int res=0;
    static int count =-1;
    static uint16_t val =-1;
    static uint16_t val1 =-1;
    static int deg=-1;
    static int deg1=-1;
    static int i=0;
    static int lastTemp=-999;
    
    TBT_THC(5,
        ,,

        temp=analogRead(TEMPERATURE),
         
        TBT_IF_TRUE(temp<MAX_TEMP_ADC,
            res=((temp*RESITOR_MEASURED)/(MAX_TEMP_ADC-temp))/100,
#ifdef DEBUG_TEMPERATURE
           debug_printf("Resistor value: %d \n",res),
#endif
            count=0,
            TBT_WHILE(count<60,
                val= (uint16_t)pgm_read_word(resistors+count), 
                TBT_IF_TRUE((val!=0) && (res<=val),
                    TBT_BLOCK(
                        val1= (uint16_t)pgm_read_word(resistors+count+1), 
                        TBT_IF_TRUE((val1==0)|| (res>=val1),
                            deg= pgm_read_byte(temperatures + count);
                            // deg1= pgm_read_byte(temperatures + count+1);
#ifdef DEBUG_TEMPERATURE
                            debug_printf("Found temperature: resistor: %d, deg:%d \n",val,deg),
#endif
                            {
                                TemperatureData data;
                                data.temperature=deg;
                                eventSystem.dispatchMessage(EventType::TEMPERATURE_CHANGE,&data);
                            },
                            count=999,
                        )
                    ),
                ),
                count++,
            )
        ),
        TBT_DELAY(1000*2),
  
       
    )

};