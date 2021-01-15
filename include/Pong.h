
#pragma once 

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "Button.h"
#include "Ball.h"
#include "Player.h"
#include "Screen.h"
#include "Updateable.h"

class Pong: public Updateable {
  public:
    Pong( std::vector<uint8_t> player_pins, uint8_t lifes, uint16_t button_lock_time, uint8_t num_leds, double stripe_length);
    void update(unsigned long runtime);

  private:
    void prepare_next_serve();
    bool autoserve_timer();
    bool ball_is_in_allowed_position();
    void choose_random_player();
    void choose_next_player();
    bool should_restart_pong();

    enum State {
      IDLE = 0,
      PLAYING,
      SERVE,
      WAITING
    } state;
    
    std::vector<Player> players;
    uint8_t num_players;
    uint8_t num_players_alive;
    Ball ball;
    unsigned long restart_lock_timestamp;
    unsigned long restart_lock_time;
    bool isFirstRun;

    unsigned long autoserve_time;
    unsigned long waiting_time;
    uint16_t auto_serve_timeout;
    uint8_t active_player;
};