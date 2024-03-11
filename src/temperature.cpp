#include <Arduino.h>
#include "temperature.h"
#include "tbt_thread.h"
#include "mylcd.h"
Temperature::Temperature()
{
// lcd.execute()
}

void Temperature::execute(){

    TBT_THC(4,
        ,,
        // Serial.println("setup text"),
        mylcd.setText(0,1,"Xin chao"),
          
            TBT_DELAY(100,80)
            // TBT_WAIT_THREAD(200, lcd)
    )

};