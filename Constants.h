
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <FastLED.h>

namespace Const {

const uint16_t POWERUP_SAFETY_DURATION = 3000;

// Player settings
const uint8_t LIFES = 6;
const uint16_t BUTTON_LOCK_TIME = 500;
const uint16_t BUTTON_PIN_RECORDING_DURATION = 6000;
const unsigned long BUTTON_PIN_RECORDING_PULSE_DURATION = 2000;

// FastLED settings
const uint8_t NUM_LEDS = 100;
const double STRIPE_LENGTH = 1.66;
//const EOrder LED_COLOR_ORDER = BGR;
//const ESPIChipsets LED_TYPE = APA102;
const uint8_t BRIGHTNESS = 64; //max. 255

const uint8_t numPlayersMin = 2;
const uint8_t numPlayersMax = 8;
//const long unsigned int  playerColors[ 8] = { CRGB::Blue, CRGB::Red, CRGB::LightGreen, CRGB::Yellow, CRGB::Magenta, CRGB::Cyan, CRGB::DarkGreen, CRGB::Orange};
const CRGB  playerColors[ 8] = { CHSV( 0, 255, 255), CHSV( 127, 255, 255), CHSV( 191, 255, 255), CHSV( 64, 255, 255), CHSV( 223, 255, 255), CHSV( 96, 255, 255), CHSV( 160, 255, 255), CHSV( 32, 255, 255)};
}


#endif
