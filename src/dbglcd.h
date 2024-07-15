#pragma once
#include <Wire.h>
#include <LiquidCrystal_Software_I2C.h>

class LCDTBT : public LiquidCrystal_I2C
{
public:
    LCDTBT();
    void startup();
};

