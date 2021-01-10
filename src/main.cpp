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
#include "PinRecordAnimator.h"

enum class GameState { RecordPins, Init, Play};

GameState state = GameState::RecordPins;

Pong * pong;
ButtonPinRecorder * bPinRecorder;
PinRecordAnimator * recordAnimator;

std::vector<Updateable*> updateables;

void setup() {
  delay( Const::POWERUP_SAFETY_DURATION_MS); // power-up safety delay

  Serial.begin( 9600);
  Serial.println("Start setup of arduino!");
  
  Screen::get(); // init screen

  bPinRecorder = new ButtonPinRecorder(Const::BUTTON_PIN_RECORDING_DURATION);
  recordAnimator = new PinRecordAnimator(Const::playerColors[0]);
  Screen::get()->add_drawable( recordAnimator, Screen::Layer::Top);
  updateables.push_back(recordAnimator);

  Serial.println("Finished setup of arduino!");
}

void loop() {
  unsigned long current_time = millis();

  for (auto updateable : updateables) {
    updateable->update(current_time);
  }

  switch (state) {
    case GameState::RecordPins: {
        uint8_t currentPinNumber = bPinRecorder->getNumRecordedButtonPins();
        CRGB currentPinColor = Const::playerColors[ currentPinNumber];
        if (currentPinColor != recordAnimator->getPulseColor()) {
          recordAnimator->setPulseColor( currentPinColor);
        }
        
        bool finished = bPinRecorder->loop();
        if ( finished) {
          state = GameState::Init;
          Screen::get()->remove_drawable(recordAnimator);
          updateables.clear();
        }

        Screen::get()->draw();
        break;
      }

    case GameState::Init: {
      Serial.println("Start initializing Pong!");
        uint8_t numButtonPins = bPinRecorder->getNumRecordedButtonPins();
        uint8_t * buttonPins = new uint8_t[ numButtonPins];
        bPinRecorder->getRecordedButtonPins( buttonPins);
        delete bPinRecorder;
        delete recordAnimator;

        pong = new Pong( buttonPins, numButtonPins, Const::LIFES, Const::BUTTON_LOCK_TIME_MS, Const::NUM_LEDS, Const::STRIPE_LENGTH);

        state = GameState::Play;
        Serial.println("Finished initializing Pong!");
        break;
      }

    case GameState::Play: {
        pong->game_logic();
        break;
      }
  }
  // delay(1000);
}
