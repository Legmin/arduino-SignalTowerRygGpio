#pragma once
#include <Arduino.h>

#include <SignalTowerRygPattern.hpp>

namespace SignalTowerRygGpio {

using SignalTowerRygPattern::ColorState;

struct Pins {
  int red = -1, yellow = -1, green = -1;
};

class Core {
 public:
  const Pins pins;
  Core(Pins pins) : pins(pins) {}

  void begin(void (*_delay)(unsigned long) = delay) {
    pinMode(pins.red, OUTPUT);
    pinMode(pins.yellow, OUTPUT);
    pinMode(pins.green, OUTPUT);
    setColors("g");
    _delay(200);
    setColors("y");
    _delay(200);
    setColors("r");
    _delay(200);
    setColors("x");
    _delay(200);
  }

  void setColors(const bool red, const bool green, const bool yellow) {
    currentColorState.r = red;
    currentColorState.g = green;
    currentColorState.y = yellow;
    setColorsByCurrentColorState();
  }

  void setColors(const ColorState& state) {
    currentColorState = state;
    setColorsByCurrentColorState();
  }

  void setColors(const String& colors) { setColors(ColorState(colors)); }

  const ColorState* pCurrentColorState() const { return &currentColorState; };

 private:
  ColorState currentColorState;

  void setColorsByCurrentColorState() {
    digitalWrite(pins.red, currentColorState.r);
    digitalWrite(pins.green, currentColorState.g);
    digitalWrite(pins.yellow, currentColorState.y);
  }
};

}  // namespace SignalTowerRygGpio
