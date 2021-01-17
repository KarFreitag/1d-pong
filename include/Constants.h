
#pragma once

#include <FastLED.h>

namespace Const
{
    const uint16_t POWERUP_SAFETY_DURATION_MS = 3000;

    // Player settings
    const uint8_t LIFES = 6;
    const uint16_t BUTTON_LOCK_TIME_MS = 500;
    const uint16_t BUTTON_PIN_RECORDING_DURATION = 6000;
    const unsigned long BUTTON_PIN_RECORDING_PULSE_DURATION_MS = 2000;
    const uint8_t recordableButtonPins[8] = { 2, 3, 4, 5, 6, 7, 8, 9};

    // FastLED settings
    const uint8_t NUM_LEDS = 100;
    const double STRIPE_LENGTH = 0.83;
    const uint8_t BRIGHTNESS = 64; //max. 255
    const int clockPin = 13;
    const int dataPin = 11;

    const uint8_t numPlayersMin = 2;
    const uint8_t numPlayersMax = 8;
    const CRGB playerColors[8] = {
        CHSV(0, 255, 255),
        CHSV(127, 255, 255),
        CHSV(191, 255, 255),
        CHSV(64, 255, 255),
        CHSV(223, 255, 255),
        CHSV(96, 255, 255),
        CHSV(160, 255, 255),
        CHSV(32, 255, 255)};
}