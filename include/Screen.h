
#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif
#include <FastLED.h>
#include <ArduinoSTL.h>

#include "Ball.h"
#include "Player.h"
#include "Drawable.h"

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

class Screen {
  public:
    enum Layer {Invisible, Bottom, Background, Players, Balls, Top};

    static Screen * get();
    
    void add_drawable(Drawable * drawable, Layer layer);
    void remove_drawable(Drawable * drawable);
    void draw();

  private:
    Screen();
    void clear();
    CRGB * leds; // TODO: make leds private again
    static Screen * instance;
    std::vector<std::pair< Drawable*, Layer>> drawables;
};