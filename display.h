#pragma once

#include <Arduino.h>

class display {
  public:
  // Classes
  static Adafruit_SH1106G oled;
  // Functions
  static void displayMain(void *parameter);
};