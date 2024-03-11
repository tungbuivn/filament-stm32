#include "led-blink.h"

void LedBlink::execute(){

    TBT_THC(5,
    ,,
   
  
    // Serial.println("Begin blink led"),
    digitalWrite(LED_BUILTIN,HIGH),
    TBT_DELAY(100,500),
    // Serial.println("End blibk led"),
    digitalWrite(LED_BUILTIN,LOW),
    TBT_DELAY(200,500)    ,
       
    )
};