#include "helper.h"

#include "Constants.h"
#include "Player.h"

std::vector<Player> createPlayers(uint8_t numPlayers, std::vector<uint8_t> player_pins, uint8_t lifes, uint8_t numLeds, uint16_t button_lock_time)
{

  std::vector<Player> newPlayers;

  for (int i = 0; i < numPlayers; ++i)
  {
    uint8_t spaceBetweenPlayers = numLeds / numPlayers - lifes;
    uint8_t hitBoxMin = i * (spaceBetweenPlayers + lifes);
    uint8_t hitBoxMax = hitBoxMin + lifes - 1;
    Player newPlayer = Player(lifes, hitBoxMin, hitBoxMax, player_pins[i], button_lock_time, Const::playerColors[i], CRGB::Black);
    newPlayers.push_back( newPlayer);
  }

  return newPlayers;
}

int8_t sgn(int8_t val)
{
  if (val < 0)
    return -1;
  if (val == 0)
    return 0;
  return 1;
}
