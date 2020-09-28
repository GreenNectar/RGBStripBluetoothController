#ifndef _SOLID_H
#define _SOLID_H

#include <Arduino.h>
#include "Style.h"

class Solid:public Style
{
  uint32_t colour;
  
  public:
    Solid(uint32_t col) : colour(col){
      
    }
    virtual void execute(Adafruit_NeoPixel*);
    virtual void start(Adafruit_NeoPixel*);
};
#endif
