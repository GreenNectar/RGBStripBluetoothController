#include "Breathe.h"

void Breathe::execute(Adafruit_NeoPixel *strip) {
  //uint8_t b = (uint8_t)abs(sin(PI * (curr / 10.0) / duration) * 255.0);
  brightness = (uint8_t)(((1.0 + sin(PI * ((millis() - starttime) / 10.0) / duration)) / 2.0) * 255.0);

  for (int i = 0; i < strip->numPixels(); i++) {
    strip->setPixelColor(i, red * brightness / 255, green * brightness / 255, blue * brightness / 255);
  }
  strip->show();
}

void Breathe::start(Adafruit_NeoPixel *strip) {
  for (int i = 0; i < strip->numPixels(); i++) {
    strip->setPixelColor(i, strip->gamma32(colour));
  }

  starttime = millis();

  red = colour >> 16;
  green = colour >> 8;
  blue = colour;
}
