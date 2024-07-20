#include "buzzer.h"
#include "pins.h"

Buzzer::Buzzer() {
    pinMode(BUZZER, OUTPUT);
    // analogWriteFrequency
    type=THREAD_EXECUTION::ONCE;
    
}

void Buzzer::execute2() {
}

void Buzzer::execute() {
    TBT_THC(5,
        // analogWrite(BUZZER,120),
        // TBT_DELAY(1000),
        // analogWrite(BUZZER,0),
       
    )
};
