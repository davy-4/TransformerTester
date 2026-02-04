#pragma once

#include <Arduino.h>

class serial {
  public:
  // Settings
  static bool fastModeEnabled;
  static bool verboseLogging;
  static bool manualModeEnabled;
  static int testCountInt;

  // Functions
  static void serialMain(void *parameter);

  // Commands
  static void help();
  static void set(String input);

  static void placeholder(const String& input);
};
