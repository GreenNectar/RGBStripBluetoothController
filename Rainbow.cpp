#include "Rainbow.h"

int pixelHue;
void Rainbow::execute(Adafruit_NeoPixel *strip){
  offset = offset + (long)(((millis() - starttime) / (100.0 * duration)) * 5 * 65536) % (5 * 65536);
  starttime = millis();
  for(int i=0; i<strip->numPixels(); i++) { 
    //pixelHue = i * 65536L / (strip->numPixels() / scale) + offset;
    strip->setPixelColor(i, strip->gamma32(strip->ColorHSV(pixelHue)));
  }
  strip->show();
}

void Rainbow::start(Adafruit_NeoPixel *strip){
  starttime = millis();
}

//double TraingleWave(double x){
//  if(x>=0&&x<PI){
//    return x;
//  }
//  else if(x>=PI&&x<2*PI){
//    return 2*PI-x;
//  }
//  else if(x>=2*PI){
//    return TraingleWave(x-2*PI);
//  }
//  else if(x<0){
//    return TraingleWave(x+2*PI);
//  }
//}
