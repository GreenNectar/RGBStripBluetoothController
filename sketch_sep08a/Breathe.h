#ifndef _BREATHE_H
#define _BREATHE_H

#include <Arduino.h>
#include "Style.h"

class Breathe:public Style
{
  uint32_t colour;
  float duration;
  uint8_t repetitions;
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t brightness;
  long starttime = millis();
  
  public:
    Breathe(uint32_t col, float dur, uint8_t rep) : colour(col), duration(dur), repetitions(rep){
      
    }
    virtual void execute(Adafruit_NeoPixel*);
    virtual void start(Adafruit_NeoPixel*);
};
#endif
