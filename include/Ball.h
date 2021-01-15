
#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif
#include "Player.h"

#include "Drawable.h"

class Ball: public Drawable {
  public:
    Ball(int8_t position, uint8_t min_position, uint8_t max_position, double speed, int8_t direction);

    void draw(CRGB *leds);

    bool is_inside_hitbox(Player &player);
    bool timer();
    int8_t get_position();
    int8_t get_previous_position();
    void set_position(int8_t p);
    int8_t get_direction();
    void set_direction(uint8_t direction);
    void reverse_direction();
    void hit();
    void advance();

    void calc_speedup(Player &player);
    void reset_speedup();

  private:
    int8_t position, previous_position;
    uint8_t min_position, max_position;
    double speed;
    double initial_speed;
    double speedup;
    int8_t direction;
    unsigned long time;
    
    // convert speed (in m/s) to timer delay
    uint16_t speed_to_timer();
    void increase_speed();
};
