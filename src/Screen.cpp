// Screen.cpp
#include "Screen.h"
#include "Constants.h"

Screen *Screen::instance = 0;

Screen::Screen()
{
  color_pallette_updates_per_second = 35;

  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;

  this->leds = new CRGB[Const::NUM_LEDS];

  // set chipset type, color order of LEDs and number of LEDs on stripe
  FastLED.addLeds<APA102, Const::dataPin, Const::clockPin, BGR>(this->leds, Const::NUM_LEDS);
  FastLED.setCorrection(TypicalLEDStrip);
  FastLED.setTemperature(UncorrectedTemperature);

  // set global brightness
  FastLED.setBrightness(Const::BRIGHTNESS);
}

Screen *Screen::get()
{
  if (!Screen::instance)
  {
    Screen::instance = new Screen();
  }
  return Screen::instance;
}

void Screen::draw_player_score(Player p)
{
  float hitbox_center = (float)(p.hitbox_max + p.hitbox_min) / 2.0f;
  uint8_t num_lost_life_leds_half = 0.5f * (float)(p.initial_lifes) * (1.0f - (float)p.lifes / (float)p.initial_lifes);

  for (uint8_t i = p.hitbox_min; i <= p.hitbox_max; ++i)
  {
    if (abs(hitbox_center - i) < num_lost_life_leds_half)
    {
      leds[i] = p.lost_lifes_color;
    }
    else
    {
      leds[i] = p.lifes_color;
    }
  }
}

void Screen::show_score(Player *players, uint8_t num_players)
{
  for (int i = 0; i < num_players; ++i)
  {
    draw_player_score(players[i]);
  }

  FastLED.show();
}

void Screen::advance_ball(Ball &b)
{
  leds[b.get_position()] = CRGB::Black;

  b.set_position(b.get_position() + b.get_direction());
  leds[b.get_position()] = CRGB::White;

  FastLED.show();
}

void Screen::clear_led(uint8_t num)
{
  leds[num] = CRGB::Black;
}

void Screen::clear_all_leds()
{
  for (uint8_t i = 0; i < Const::NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
  }
}

void Screen::clear(Ball &ball)
{
  clear_led(ball.get_position());
}

void Screen::reset(Player *players, uint8_t num_players)
{
  clear_all_leds();
  show_score(players, num_players);
}

void Screen::draw_ball(uint8_t num)
{
  leds[num] = CRGB::White;
}

void Screen::draw(Player *players, uint8_t num_players, Ball &ball)
{
  clear_led(ball.get_previous_position());

  for (int i = 0; i < num_players; ++i)
  {
    draw_player_score(players[i]);
  }

  draw_ball(ball.get_position());
  FastLED.show();
}

void Screen::add_drawable(Drawable *drawable, Layer layer)
{
  this->drawables.push_back(std::pair<Drawable *, Layer>(drawable, layer));
}

void Screen::remove_drawable(Drawable * drawable)
{
  for (auto it = this->drawables.begin(); it != drawables.end(); ++it)
  {
    if (it->first == drawable) {
      this->drawables.erase(it);
      return;
    }
  }
}

void Screen::draw()
{
  for (int layer=Layer::Bottom; layer <= Layer::Top; layer++) {
    for (auto it : this->drawables) {
      if (it.second == layer) {
        it.first->draw(this->leds);
      }
    }
  }

  FastLED.show();
}
