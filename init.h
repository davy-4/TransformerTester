#pragma once

#include <Arduino.h>

class init {
  public:
  // Variables
  static long init::start;
  static long init::current;

  // Functions
  static void init::initialize();
};