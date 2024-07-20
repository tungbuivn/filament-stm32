#include "base-sprite.h"
#include "mylcd.h"
#include "TFT_eSPI.h"
BaseSprite::BaseSprite(int ax, int ay, int aw, int ah) {
    x = ax;
    y = ay;
    w = aw;
    h = ah;
    transparent=TFT_BLACK;
}
BaseSprite::BaseSprite(int ax, int ay, int aw, int ah, int atransparent)
{
    BaseSprite(ax,ay,aw,ah);
    transparent = atransparent;
    
}
void BaseSprite::begin(int aangle)
{
    angle=aangle;
    if (!buf) {
        buf = (uint16_t *)malloc(((w) + 2) * ((h) + 2) * 2);
        mylcd->tft->readRect(x, y, w, h, buf);
    }
    if (!sp) {
        sp = new TFT_eSprite(mylcd->tft);
    }
    
    sp->setColorDepth(8); // Set colour depth first
    sp->createSprite(w, h); // then create the sprite
    sp->fillSprite(transparent);
    
}
void BaseSprite::end() {
    mylcd->tft->pushRect(x, y, w, h, buf);
    if (angle)
         mylcd->tft->setPivot(x+w/2,y+h/2);
    if (angle==0)
        sp->pushSprite(x, y, transparent);
    else
        sp->pushRotated(rotateAngle,transparent);
    sp->deleteSprite();
    mylcd->tft->setPivot(0,0);
    rotateAngle+=angle;
    if (rotateAngle>360) rotateAngle-=360;
    if (rotateAngle<-360) rotateAngle+=360;
}
BaseSprite::~BaseSprite() {
    if (sp) delete sp;
    if (buf) free(buf);
}