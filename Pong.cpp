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

Pong::Pong(uint8_t * player_pins, uint8_t num_players, uint8_t lifes, uint16_t button_lock_time,
           uint8_t num_leds, double stripe_length, uint8_t brightness,
           uint8_t restart_pin, uint16_t restart_lock_time, uint8_t random_seed_pin)
  : num_players( num_players),
    screen(num_leds, brightness),
    restart(restart_pin, restart_lock_time),
    ball(0, 0, num_leds - 1, 0.2, 1)
{
  players = createPlayers( num_players, player_pins, lifes, num_leds, button_lock_time);

  state = WAITING;
  auto_serve_timeout = 2000;
  position_is_allowed = false;
  waiting_time = millis();
  randomSeed(analogRead(random_seed_pin));
}

void Pong::game_logic() {
  if (restart.is_pressed()) {
    screen.clear(ball);
    waiting_time = millis();
    state = WAITING;
  }

  switch (state) {
    case WAITING:
      screen.show_score( players, num_players);
      if (restart.is_pressed()) {
        choose_random_player();

        for (int i=0; i<num_players; ++i) {
          players[i].reset_lifes();  
        }
        screen.reset( players, num_players);

        state = SERVE;
      }
      if (millis() - waiting_time >= 30000) {
        state = IDLE;
      }
      break;
    case IDLE:
      screen.show_color_palette();
      if (restart.is_pressed()) {
        screen.reset( players, num_players);
        waiting_time = millis();
        state = WAITING;
      }
      break;
    case PLAYING:
      if (ball.timer()) {
        ball.advance();
        screen.draw( players, num_players, ball);
      }

      if ( players[ active_player].is_position_within_hitbox( ball.get_previous_position())
           && !players[ active_player].is_position_within_hitbox( ball.get_position())) {
        if ( players[ active_player].lose_life() == 0 ) {
          screen.reset( players, num_players);
          waiting_time = millis();
          state = WAITING;
          break;
        }
        screen.show_score( players, num_players);
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
      // as long as auto_serve_timeout isn't reached, advance ball and calculate speedup for current position
      if ( autoserve_timer() ) {
        if ( autoserve_step_timer()) {
          position_is_allowed = true;
          ball.advance();
          ball.calc_speedup( players[active_player]);
          autoserve_step_time = millis();
        }
      } else {
        ball.reset_speedup();
        choose_next_player();
        // reset flag
        position_is_allowed = false;
        state = PLAYING;
      }
      // Wait at least one loop for ball to come back in the court ()
      if (players[active_player].button.is_pressed() && position_is_allowed) {
        // reset flag
        choose_next_player();
        position_is_allowed = false;
        state = PLAYING;
      }
      break;
  }
}

void Pong::prepare_next_serve() {
  ball.reverse_direction();
  ball.reset_speedup();
  autoserve_time = millis();
  autoserve_step_time = millis();
  state = SERVE;
}

bool Pong::autoserve_timer() {
  return (millis() - autoserve_time <= auto_serve_timeout);
}

bool Pong::autoserve_step_timer() {
  return (millis() - autoserve_step_time >= (2000 / 8));
}

bool Pong::ball_is_in_allowed_position() {
  for (int i=0; i<num_players; ++i) {
    if ( players[i].is_position_within_hitbox( ball.get_position())) {
      return true;
    }
  }
  return false;
}

void Pong::choose_random_player() {
  // randomly select active player to serve the first ball
  active_player = random(0, 2);
  int8_t ball_position = (players[ active_player].hitbox_max - players[ active_player].hitbox_min) / 2;
  ball.set_position( ball_position);

  int8_t ball_direction = random(0, 1) ? 1 : -1;
  ball.set_direction( ball_direction);

  choose_next_player();
}

void Pong::choose_next_player() {
  int8_t next_player_direction = sgn( ball.get_direction());
  active_player = ((active_player + next_player_direction) + num_players) % num_players;
}
