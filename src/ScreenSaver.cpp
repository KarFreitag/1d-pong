
#include "ScreenSaver.h"

#include "Constants.h"

ScreenSaver::ScreenSaver() : animator(Const::NUM_LEDS)
{
    this->animator.setPulseColor(CRGB::RoyalBlue);
    this->animator.setPulseDuration(10000);

    this->lastActionTime = 0;
    this->activationTime = 30000;
}

ScreenSaver::~ScreenSaver()
{
}

void ScreenSaver::update(unsigned long runtime)
{
    this->currentTime = runtime;

    uint8_t numRecordablePins = sizeof(Const::recordableButtonPins);
    for (uint8_t i = 0; i < numRecordablePins; ++i)
    {
        if (digitalRead(Const::recordableButtonPins[i]) == HIGH)
        {
            this->lastActionTime = runtime;
            break;
        }
    }
}

void ScreenSaver::draw(CRGB *leds)
{
    if (this->currentTime - this->lastActionTime > this->activationTime)
    {
        this->animator.animateLeds(leds, this->currentTime);
    }
}
