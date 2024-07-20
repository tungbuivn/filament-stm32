#pragma once
#include "TFT_eSPI.h"

#define DRAW_SPRITE(bsp,...) { \
        bsp->begin(0);\
        TFT_eSprite *sp = bsp->sp; \
        draw(bsp,sp,__VA_ARGS__); \
        bsp->end();\
    } 

#define DRAW_ROTATE_SPRITE(bsp,ang,...) { \
        bsp->begin(ang);\
        TFT_eSprite *sp = bsp->sp; \
        draw(bsp,sp,__VA_ARGS__); \
        bsp->end();\
    } 


class BaseSprite {
     uint16_t *buf=NULL;
     int rotateAngle=0;
     int angle=0;
protected:
   
   
   
    // virtual void onDraw()=0;
public:

    int x;
    int y;
    int w;
    int h;
    int transparent;
    TFT_eSprite *sp=NULL;
    BaseSprite(int x,int y,int w,int h);
    BaseSprite(int x,int y,int w,int h,int transparent);
    ~BaseSprite();
    void begin(int angle);
    void end();
};


