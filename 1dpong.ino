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

// 1dpong.ino
#include "Pong.h"
#include "ButtonPinRecorder.h"

// Player settings
const uint8_t LIFES = 8;
const uint16_t BUTTON_LOCK_TIME = 1000;
const uint16_t BUTTON_PIN_RECORDING_DURATION = 3000;

// FastLED settings
const uint8_t NUM_LEDS = 100;
const double STRIPE_LENGTH = 1.66;
//const EOrder LED_COLOR_ORDER = BGR;
//const ESPIChipsets LED_TYPE = APA102;
const uint8_t BRIGHTNESS = 64; //max. 255

enum class GameState { InitPinRecorder, RecordPins, InitPong, PlayPong};

GameState state = GameState::InitPinRecorder;

Pong * pong;
ButtonPinRecorder * bPinRecorder;

void setup() {
  Serial.begin( 9600 );
  Serial.println("Starting Pong!");
}

void loop() {
  switch (state) {
    case GameState::InitPinRecorder: {
        bPinRecorder = new ButtonPinRecorder( BUTTON_PIN_RECORDING_DURATION);
        state = GameState::RecordPins;
        break;
      }

    case GameState::RecordPins: {
        bool buttonPinsRecorded = bPinRecorder->loop();
        if (buttonPinsRecorded) {
          state = GameState::InitPong;
        }
        break;
      }

    case GameState::InitPong: {
        uint8_t numButtonPins = bPinRecorder->getNumRecordedButtonPins();
        uint8_t * buttonPins = new uint8_t[ numButtonPins];
        bPinRecorder->getRecordedButtonPins( buttonPins);
        delete bPinRecorder;
        
        pong = new Pong( buttonPins, numButtonPins, LIFES, BUTTON_LOCK_TIME, NUM_LEDS, STRIPE_LENGTH, BRIGHTNESS);

        state = GameState::PlayPong;
        break;
      }

    case GameState::PlayPong: {
        pong->game_logic();
        break;
      }
  }
}

