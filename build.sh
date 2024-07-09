#!/bin/bash

rm -rf .pio/libdeps/stm32f401ccu6/tbt_thread
rm -rf .pio/libdeps/stm32f401ccu6/Adafruit\ MAX31865\ library
rm -rf .pio/libdeps/stm32f401ccu6/ST7567S_128X64_I2C

pio run -e stm32f401ccu6