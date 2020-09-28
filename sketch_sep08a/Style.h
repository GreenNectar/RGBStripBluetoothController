#ifndef _STYLE_H
#define _STYLE_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class Style
{
  public:
    Style();
    virtual void execute(Adafruit_NeoPixel*);
    virtual void start(Adafruit_NeoPixel*);
    void setduration(int);
    bool finished = false;
  private:
    int _duration;
};


#endif
