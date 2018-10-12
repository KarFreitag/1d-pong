#include "helper.h"

#include "Player.h"

Player * createPlayers( uint8_t numPlayers, uint8_t * player_pins, uint8_t lifes, uint8_t numLeds, uint16_t button_lock_time) {
  long unsigned int  playerColors[ numPlayers] = { CRGB::Green, CRGB::Blue};

  Player * newPlayers = new Player[ numPlayers];
  newPlayers[0] = Player(lifes, 0, lifes - 1, player_pins[0], button_lock_time, playerColors[0], CRGB::Red);
  newPlayers[1] = Player(lifes, numLeds - lifes, numLeds - 1, player_pins[1], button_lock_time, playerColors[1], CRGB::Red);

  return newPlayers;
}

