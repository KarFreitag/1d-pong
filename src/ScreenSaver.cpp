
#include "ScreenSaver.h"

#include "Constants.h"

ScreenSaver::ScreenSaver() : animator(Const::NUM_LEDS)
{
    this->animator.setPulseColor(CRGB::RoyalBlue);
    this->animator.setPulseDuration(10000);

    this->lastActionTime = 0;
    this->activationTime = 10000;
}

ScreenSaver::~ScreenSaver()
{
}

void ScreenSaver::update(unsigned long runtime)
{
    this->currentTime = runtime;
}

void ScreenSaver::draw(CRGB *leds)
{
    if (this->currentTime - this->lastActionTime > this->activationTime)
    {
        this->animator.animateLeds(leds, this->currentTime);
    }
}
