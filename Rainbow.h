#ifndef _RAINBOW_H
#define _RAINBOW_H

#include <Arduino.h>
#include "Style.h"

class Rainbow:public Style
{
  float duration = 1;
  float scale = 1;
  long offset;
  long starttime = millis();
  
  public:
    Rainbow(float newduration, float newscale) : duration(newduration), scale(newscale){
      
    }
    virtual void execute(Adafruit_NeoPixel*);
    virtual void start(Adafruit_NeoPixel*);
};
#endif
