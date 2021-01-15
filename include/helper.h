// helper.h
#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <ArduinoSTL.h>

class Player;

std::vector<Player> createPlayers(uint8_t numPlayers, std::vector<uint8_t> player_pins, uint8_t lifes, uint8_t numLeds, uint16_t button_lock_time);

int8_t sgn(int8_t val);

template <class T>
void remove_from_vector(std::vector<T> &vec, T value)
{
  auto it = std::find(vec.begin(), vec.end(), value);

  if (it != vec.end())
  {
    vec.erase(it);
  }
}