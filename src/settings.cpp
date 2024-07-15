#include "I2C_eeprom.h"
#include "settings.h"
#include "pins.h"

I2C_eeprom ee(0x50);
Settings::Settings() {
    Wire.begin();

    ee.begin();
    if (! ee.isConnected())
    {
        debug_printf("ERROR: Can't find eeprom\n");
    }
    debug_printf("isConnected: %d\n",ee.isConnected());


}
bool inited=false;
void Settings::loadSettings() {
    const int len=20;
    uint8_t buf[len];
    ee.readBlock(EEPROM_OFFSET,buf,len);
}
void Settings::execute() {
    TBT_THC(5,
        TBT_IF_TRUE(!inited,
            inited=true,
            loadSettings(),
        ),
    )
}