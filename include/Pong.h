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

// Pong.h
#ifndef PONG_H
#define PONG_H

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "Button.h"
#include "Ball.h"
#include "Player.h"
#include "Screen.h"

class Pong {
  public:
    Pong(uint8_t * player_pins, uint8_t num_players, uint8_t lifes, uint16_t button_lock_time,
         CRGB *leds, uint8_t num_leds, double stripe_length);

    void game_logic();

  private:
    enum State {
      IDLE = 0,
      DEMO,
      PLAYING,
      SERVE,
      WAITING
    } state;
    
    Player* players;
    uint8_t num_players;
    uint8_t num_players_alive;
    Screen screen;
    Ball ball;
    unsigned long restart_lock_timestamp;
    unsigned long restart_lock_time;
    bool isFirstRun;

    unsigned long autoserve_time;
    unsigned long waiting_time;
    uint16_t auto_serve_timeout;
    uint8_t active_player;
    void prepare_next_serve();
    bool autoserve_timer();
    bool ball_is_in_allowed_position();
    void choose_random_player();
    void choose_next_player();
    bool should_restart_pong();
};

#endif
