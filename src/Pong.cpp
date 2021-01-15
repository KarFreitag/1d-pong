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

// Pong.cpp
#include "Pong.h"

#include "helper.h"

Pong::Pong( std::vector<uint8_t> player_pins, uint8_t lifes, uint16_t button_lock_time, uint8_t num_leds, double stripe_length)
  : num_players( player_pins.size()),
    num_players_alive( num_players),
    ball(0, 0, num_leds - 1, 0.2, 1),
    restart_lock_time( button_lock_time)
{
  players = createPlayers( num_players, player_pins, lifes, num_leds, button_lock_time);

  for (auto player = players.begin(); player != players.end(); ++player) {
    Screen::get()->add_drawable(player, Screen::Layer::Players);
  }

  Screen::get()->add_drawable( &ball, Screen::Layer::Balls);

  state = WAITING;
  auto_serve_timeout = 2000;
  waiting_time = millis();
  isFirstRun = true;
  randomSeed( millis());
}

void Pong::update(unsigned long runtime)
{
 if (should_restart_pong()) {
    waiting_time = runtime;
    state = WAITING;
  }

  switch (state) {
    case WAITING:
      if (should_restart_pong() || (isFirstRun && (runtime - waiting_time >= 10000))) {
        choose_random_player();

        for (int i = 0; i < num_players; ++i) {
          players[i].reset_lifes();
        }
        num_players_alive = num_players;
        state = SERVE;
      }
      if (runtime - waiting_time >= 30000) {
        state = IDLE;
      }
      break;
      
    case IDLE:
      // TODO: update screen saver
      break;
      
    case PLAYING:
      if (ball.timer()) {
        ball.advance();
      }

      if ( players[ active_player].is_position_within_hitbox( ball.get_previous_position())
           && !players[ active_player].is_position_within_hitbox( ball.get_position())) {

        if ( players[ active_player].lose_life() == 0 ) {
          --num_players_alive;

          if (num_players_alive <= 1) {
            waiting_time = runtime;
            state = WAITING;
            break;
          }
        }
        prepare_next_serve();
        break;
      }

      if (players[ active_player].button.is_pressed() && players[ active_player].is_position_within_hitbox( ball.get_position())) {
        ball.hit();
        ball.calc_speedup( players[ active_player]);
        choose_next_player();
      }
      break;
      
    case SERVE:
      if ( !autoserve_timer() ) {
        // auto-serve
        ball.reset_speedup();
        choose_next_player();
        state = PLAYING;
      }

      if ( players[active_player].button.is_pressed()) {
        // perform serve
        choose_next_player();
        state = PLAYING;
      }
      break;
  }
}

void Pong::prepare_next_serve() {
  ball.reverse_direction();
  ball.reset_speedup();
  autoserve_time = millis();
  state = SERVE;
}

bool Pong::autoserve_timer() {
  return (millis() - autoserve_time <= auto_serve_timeout);
}

bool Pong::ball_is_in_allowed_position() {
  for (int i = 0; i < num_players; ++i) {
    if ( players[i].is_position_within_hitbox( ball.get_position())) {
      return true;
    }
  }
  return false;
}

void Pong::choose_random_player() {
  // randomly select active player to serve the first ball
  active_player = random( num_players);
  int8_t ball_position = (players[ active_player].hitbox_max + players[ active_player].hitbox_min) / 2;
  ball.set_position( ball_position);

  int8_t ball_direction = random( 2) ? 1 : -1;
  ball.set_direction( ball_direction);
}

void Pong::choose_next_player() {
  int8_t next_player_direction = sgn( ball.get_direction());
  active_player = ((active_player + next_player_direction) + num_players) % num_players;

  if ( players[ active_player].lifes <= 0) {
    choose_next_player();
  }
}

bool Pong::should_restart_pong() {
  for (int i = 0; i < num_players; ++i) {
    if ( !(digitalRead( players[ i].button.pin) == HIGH)) {
      restart_lock_timestamp = millis();
      return false;
    }
  }

  if ( millis() - restart_lock_timestamp > restart_lock_time) {
    restart_lock_timestamp = millis();
    return true;
  } else {
    return false;  
  }
}
