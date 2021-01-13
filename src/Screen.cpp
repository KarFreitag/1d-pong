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

void Screen::clear()
{
  for (uint8_t i = 0; i < Const::NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
  }
}

void Screen::reset(std::vector<Player> players, uint8_t num_players)
{
  clear();
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
  this->clear();

  for (int layer=Layer::Bottom; layer <= Layer::Top; layer++) {
    for (auto it : this->drawables) {
      if (it.second == layer) {
        it.first->draw(this->leds);
      }
    }
  }

  FastLED.show();
}
