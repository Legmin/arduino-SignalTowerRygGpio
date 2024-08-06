#pragma once
#include <Arduino.h>

#include <SignalTowerRygPattern.hpp>

namespace SignalTowerRygGpio {

using SignalTowerRygPattern::ColorState;

class Core {
 public:
  const int pinRed, pinYellow, pinGreen;
  Core(const int pinRed, const int pinYellow, const int pinGreen)
      : pinRed(pinRed), pinYellow(pinYellow), pinGreen(pinGreen) {}

  void begin(void (*_delay)(unsigned long) = delay) {
    pinMode(pinRed, OUTPUT);
    pinMode(pinYellow, OUTPUT);
    pinMode(pinGreen, OUTPUT);
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
    digitalWrite(pinRed, currentColorState.r);
    digitalWrite(pinGreen, currentColorState.g);
    digitalWrite(pinYellow, currentColorState.y);
  }
};

}  // namespace SignalTowerGpio
