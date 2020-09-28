#include "Gradient.h"

void Gradient::execute(Adafruit_NeoPixel *strip){
  //offset = ;
  int curr = 0;
  int pixels = strip->numPixels();
  uint32_t currcol;
  uint32_t prevcol;
  for (int i = 0; i < pixels; i++) {
    int prevcol = (int(floor((i - 1) / (pixels / colamount))) - 1) % colamount;;
    int currcol = int(floor((i - 1) / (pixels / colamount))) % colamount;
    int nextcol = (int(floor((i - 1) / (pixels / colamount))) + 1) % colamount;

    strip->setPixelColor(i, prevcol );
    
    //strip->setPixelColor(i, colours[int(floor((i - 1) / (strip->numPixels() / colamount)))]);
    //1.0 + sin(PI * (i / pixels));
    //strip->setPixelColor(i, colours[i % colamount]);
  }
  strip->show();
}

void Gradient::start(Adafruit_NeoPixel *strip){
  starttime = millis();
}
