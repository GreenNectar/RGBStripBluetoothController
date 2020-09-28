#ifndef _GRADIENT_H
#define _GRADIENT_H

#define GRADIENTCOLOURSIZE 18
#define ELEMENT_COUNT_MAX 18

#include <Arduino.h>
#include "Style.h"

class Gradient:public Style
{
  long starttime = millis();
  int colamount;
//  uint8_t red[];
//  uint8_t green[];
//  uint8_t blue[];
  uint32_t colours[];
  
  public:
    Gradient(uint32_t col[], int amount, float spd){
      for(int i = 0; i < amount; i++){
//        red[i] = col[i] >> 16;
//        green[i] = col[i] >> 8;
//        blue[i] = col[i];
        colours[i] = col[i];
      }
      colamount = amount;
    }
    virtual void execute(Adafruit_NeoPixel*);
    virtual void start(Adafruit_NeoPixel*);
};
#endif
