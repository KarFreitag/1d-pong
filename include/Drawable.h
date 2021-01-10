
#pragma once

#include <FastLED.h>

class Drawable
{
public:
    virtual ~Drawable() {}
    virtual void draw(CRGB * leds);
};