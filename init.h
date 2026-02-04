#pragma once

#include <Arduino.h>

class init {
  public:
  // Variables
  static long start;
  static long current;

  // Functions
  static void initialize();
};