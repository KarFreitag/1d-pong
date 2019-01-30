
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <FastLED.h>

namespace Const {

const uint16_t POWERUP_SAFETY_DURATION = 3000;

// Player settings
const uint8_t LIFES = 8;
const uint16_t BUTTON_LOCK_TIME = 1000;
const uint16_t BUTTON_PIN_RECORDING_DURATION = 6000;
const unsigned long BUTTON_PIN_RECORDING_PULSE_DURATION = 2000;

// FastLED settings
const uint8_t NUM_LEDS = 100;
const double STRIPE_LENGTH = 1.66;
//const EOrder LED_COLOR_ORDER = BGR;
//const ESPIChipsets LED_TYPE = APA102;
const uint8_t BRIGHTNESS = 64; //max. 255


const long unsigned int  playerColors[ 6] = { CRGB::Green, CRGB::Blue, CRGB::Red, CRGB::Yellow, CRGB::Cyan, CRGB::Magenta};
}


#endif
