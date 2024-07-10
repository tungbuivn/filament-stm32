#include "buzzer.h"
#include "pins.h"

Buzzer::Buzzer() {
     pinMode(BUZZER, OUTPUT);
    
}
void Buzzer::execute(){

    TBT_THC(5,
    ,,
        // Serial.println("Begin blink led"),
    
        TBT_DELAY(500),
    )
};