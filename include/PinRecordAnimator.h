
#pragma once

#include "ColorStripeAnimatorPulse.h"
#include "Drawable.h"
#include "Updateable.h"

class PinRecordAnimator : public ColorStripeAnimatorPulse, public Drawable, public Updateable
{
public:
    PinRecordAnimator(CRGB color);
    ~PinRecordAnimator();

    void draw(CRGB * leds);
    void update(unsigned long runtime);

private:
    unsigned long current_time;
};