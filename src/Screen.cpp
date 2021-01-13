// Screen.cpp
#include "Screen.h"
#include "Constants.h"

Screen *Screen::instance = 0;

Screen::Screen()
{
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

void Screen::reset(std::vector<Player> players, uint8_t num_players)
{
  clear_all_leds();
}

void Screen::draw_ball(uint8_t num)
{
  leds[num] = CRGB::White;
}

void Screen::draw(std::vector<Player> players, uint8_t num_players, Ball &ball)
{
  clear_led(ball.get_previous_position());

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
  this->clear_all_leds();

  for (int layer=Layer::Bottom; layer <= Layer::Top; layer++) {
    for (auto it : this->drawables) {
      if (it.second == layer) {
        it.first->draw(this->leds);
      }
    }
  }

  FastLED.show();
}
