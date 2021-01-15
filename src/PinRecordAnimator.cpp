
#include "PinRecordAnimator.h"
#include "Constants.h"

PinRecordAnimator::PinRecordAnimator(CRGB color) : ColorStripeAnimatorPulse(Const::NUM_LEDS)
{
    this->setPulseColor(color);
    this->setPulseDuration(Const::BUTTON_PIN_RECORDING_PULSE_DURATION_MS);

    this->current_time = 0;
}

PinRecordAnimator::~PinRecordAnimator() {}

void PinRecordAnimator::draw(CRGB * leds) {
    this->animateLeds(leds, this->current_time);
}

void PinRecordAnimator::update(unsigned long runtime) {
    this->current_time = runtime;
}