#include "Solid.h"

void Solid::execute(Adafruit_NeoPixel *strip){
  
}

void Solid::start(Adafruit_NeoPixel *strip){
  for(int i = 0; i < strip->numPixels(); i++){
    strip->setPixelColor(i, strip->gamma32(colour));
  }
  strip->show();
}
