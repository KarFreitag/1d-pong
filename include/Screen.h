/*
 * 1D Pong - Pong-like game run on an Arduino MCU
 * Copyright (C) 2018  Stephan Riedel - raidlman@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// Screen.h
#ifndef SCREEN_H
#define SCREEN_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif
#include <FastLED.h>
#include <ArduinoSTL.h>

#include "Ball.h"
#include "Player.h"
#include "Drawable.h"

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

class Screen {
  public:
    enum Layer {Invisible, Bottom, Background, Top};

    static Screen * get();
    void show_score( Player * players, uint8_t num_players);
    void advance_ball( Ball &b);
    void draw(Player * players, uint8_t num_players, Ball &ball);
    void clear(Ball &ball);
    void reset( Player * players, uint8_t num_players);

    CRGB * leds; // TODO: make leds private again
    void add_drawable(Drawable * drawable, Layer layer);
    void remove_drawable(Drawable * drawable);
    void draw();

  private:
    Screen();
    void draw_player_score(Player p);
    void clear_led(uint8_t num);
    void clear_all_leds();
    void draw_ball(uint8_t num);

    static Screen * instance;
    std::vector<std::pair< Drawable*, Layer>> drawables;
    uint8_t color_pallette_updates_per_second;
    CRGBPalette16 currentPalette;
    TBlendType currentBlending;
};

#endif
