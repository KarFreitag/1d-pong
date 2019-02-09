/*
   1D Pong - Pong-like game run on an Arduino MCU
   Copyright (C) 2018  Stephan Riedel - raidlman@gmail.com

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <FastLED.h>

// 1dpong.ino
#include "Pong.h"
#include "ButtonPinRecorder.h"
#include "Constants.h"
#include "ColorStripeAnimatorPulse.h"

enum class GameState { InitPinRecorder, RecordPins, InitPong, PlayPong};

GameState state = GameState::InitPinRecorder;

Pong * pong;
ButtonPinRecorder * bPinRecorder;
ColorStripeAnimatorPulse * pulseStripeAnimator;
CRGB * leds = new CRGB[ Const::NUM_LEDS];

void setup() {
  delay( Const::POWERUP_SAFETY_DURATION); // power-up safety delay

  // set chipset type, color order of LEDs and number of LEDs on stripe
  //FastLED.addLeds<led_type, led_color_order>(leds, num_leds);
  FastLED.addLeds<APA102, BGR>(leds, Const::NUM_LEDS);
  FastLED.setCorrection( TypicalLEDStrip );
  FastLED.setTemperature( UncorrectedTemperature);
  
  // set global brightness
  FastLED.setBrightness( Const::BRIGHTNESS );

  // turn off all LEDs
  for (uint8_t i = 0; i < Const::NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }

  FastLED.show();

  Serial.begin( 9600 );
  Serial.println("Starting Pong!");
}

void loop() {
//  for (int i=2; i<10; ++i) {
//    Serial.println( "Pin" + String( i) + " " + String( digitalRead( i)));  
//  }
//  Serial.println( "");
//  delay( 1000);

  
  switch (state) {
    case GameState::InitPinRecorder: {
      Serial.println("Initializing pin recorder!");
        bPinRecorder = new ButtonPinRecorder( Const::BUTTON_PIN_RECORDING_DURATION);
        pulseStripeAnimator = new ColorStripeAnimatorPulse( Const::NUM_LEDS);
        pulseStripeAnimator->setPulseColor( Const::playerColors[ 0]);
        pulseStripeAnimator->setPulseDuration( Const::BUTTON_PIN_RECORDING_PULSE_DURATION);
        state = GameState::RecordPins;
        break;
      }

    case GameState::RecordPins: {
        pulseStripeAnimator->animateLeds( leds, millis());
        FastLED.show();

        uint8_t currentPinNumber = bPinRecorder->getNumRecordedButtonPins();
        CRGB currentPinColor = Const::playerColors[ currentPinNumber];
        if (currentPinColor != pulseStripeAnimator->getPulseColor()) {
          pulseStripeAnimator->setPulseColor( currentPinColor);
        }
        
        bool finished = bPinRecorder->loop();
        if ( finished) {
          state = GameState::InitPong;
        }
        break;
      }

    case GameState::InitPong: {
      Serial.println("Initializing Pong!");
        uint8_t numButtonPins = bPinRecorder->getNumRecordedButtonPins();
        uint8_t * buttonPins = new uint8_t[ numButtonPins];
        bPinRecorder->getRecordedButtonPins( buttonPins);
        delete bPinRecorder;
        delete pulseStripeAnimator;

        pong = new Pong( buttonPins, numButtonPins, Const::LIFES, Const::BUTTON_LOCK_TIME, leds, Const::NUM_LEDS, Const::STRIPE_LENGTH);

        state = GameState::PlayPong;
        break;
      }

    case GameState::PlayPong: {
        pong->game_logic();
        break;
      }
  }
}

