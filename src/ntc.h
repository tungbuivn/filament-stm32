#include <Arduino.h>

const char temperatures[] PROGMEM = {

    0, 1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13, 14, 15, 16,
    17,
    18, 19,
    20, 21,
    22, 23,
    24, 25,
    26, 27,
    28, 29,
    30, 31,
    32, 33,
    34, 35,
    36, 37,
    38, 39,
    40, 41,
    42, 43,
    44, 45,
    46, 47,
    48, 49,
    50, 51,
    52, 53,
    54, 55,
    56, 57,
    58, 59,
    60};


// this temp was scale down 100 times to storable in 2 bytes 
const uint16_t resistors[] PROGMEM = {
 
    3211,
    3054,
    2906,
    2766,
    2634,
    2508,
    2390,
    2277,
    2171,
    2070,
    1985,
    1883,
    1797,
    1715,
    1637,
    1564,
    1494,
    1427,
    1364,
    1304,
    1246,
    1192,
    1140,
    1091,
    1044,
    1000,
    957,
    916,
    878,
    841,
    806,
    773,
    741,
    710,
    681,
    653,
    627,
    602,
    578,
    555,
    533,
    511,
    491,
    472,
    454,
    436,
    419,
    403,
    388,
    373,
    358,
    345,
    332,
    320,
    308,
    297,
    286,
    275,
    265,
    256,
    246,
    0


};