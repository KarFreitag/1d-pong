
#pragma once

#include <ColorStripeAnimatorPulse.h>

#include "Updateable.h"
#include "Drawable.h"

class ScreenSaver: public Updateable, public Drawable
{
public:
    ScreenSaver();
    ~ScreenSaver();

    void update(unsigned long runtime);
    void draw(CRGB *leds);

private:
    unsigned long activationTime;
    unsigned long lastActionTime;
    unsigned long currentTime;
    ColorStripeAnimatorPulse animator;
};