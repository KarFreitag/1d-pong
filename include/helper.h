// helper.h
#ifndef HELPER_H
#define HELPER_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

class Player;

Player * createPlayers( uint8_t numPlayers, uint8_t * player_pins, uint8_t lifes, uint8_t numLeds, uint16_t button_lock_time);
int8_t sgn(int8_t val);

#endif
