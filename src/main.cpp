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

enum class GameState { RecordPins, Init, Play};

GameState state = GameState::RecordPins;

Pong * pong;
ButtonPinRecorder * bPinRecorder;
ColorStripeAnimatorPulse * pulseStripeAnimator;

void setup() {
  delay( Const::POWERUP_SAFETY_DURATION_MS); // power-up safety delay

  Serial.begin( 9600);
  Serial.println("Start setup of arduino!");
  
  Screen::get(); // init screen

  bPinRecorder = new ButtonPinRecorder(Const::BUTTON_PIN_RECORDING_DURATION);
  pulseStripeAnimator = new ColorStripeAnimatorPulse(Const::NUM_LEDS);
  pulseStripeAnimator->setPulseColor(Const::playerColors[0]);
  pulseStripeAnimator->setPulseDuration(Const::BUTTON_PIN_RECORDING_PULSE_DURATION_MS);

  Serial.println("Finished setup of arduino!");
}

void loop() {
  switch (state) {
    case GameState::RecordPins: {
        pulseStripeAnimator->animateLeds( Screen::get()->leds, millis());
        FastLED.show();

        uint8_t currentPinNumber = bPinRecorder->getNumRecordedButtonPins();
        CRGB currentPinColor = Const::playerColors[ currentPinNumber];
        if (currentPinColor != pulseStripeAnimator->getPulseColor()) {
          pulseStripeAnimator->setPulseColor( currentPinColor);
        }
        
        bool finished = bPinRecorder->loop();
        if ( finished) {
          state = GameState::Init;
        }
        break;
      }

    case GameState::Init: {
      Serial.println("Initializing Pong!");
        uint8_t numButtonPins = bPinRecorder->getNumRecordedButtonPins();
        uint8_t * buttonPins = new uint8_t[ numButtonPins];
        bPinRecorder->getRecordedButtonPins( buttonPins);
        delete bPinRecorder;
        delete pulseStripeAnimator;

        pong = new Pong( buttonPins, numButtonPins, Const::LIFES, Const::BUTTON_LOCK_TIME_MS, Const::NUM_LEDS, Const::STRIPE_LENGTH);

        state = GameState::Play;
        break;
      }

    case GameState::Play: {
        pong->game_logic();
        break;
      }
  }
}
