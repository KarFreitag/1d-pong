#include "helper.h"

#include "Player.h"

Player * createPlayers( uint8_t numPlayers, uint8_t * player_pins, uint8_t lifes, uint8_t numLeds, uint16_t button_lock_time) {
  long unsigned int  playerColors[ 6] = { CRGB::Green, CRGB::Blue, CRGB::Red, CRGB::Yellow, CRGB::Cyan, CRGB::Magenta};

  Player * newPlayers = new Player[ numPlayers];

  for ( int i=0; i<numPlayers; ++i) {
    uint8_t spaceBetweenPlayers = numLeds / numPlayers - lifes;
    uint8_t hitBoxMin = i * (spaceBetweenPlayers + lifes);
    uint8_t hitBoxMax = hitBoxMin + lifes - 1; 
    newPlayers[i] = Player(lifes, hitBoxMin, hitBoxMax, player_pins[i], button_lock_time, playerColors[i], CRGB::Black);  
  }

  return newPlayers;
}

