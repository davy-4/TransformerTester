#pragma once

#include <Arduino.h>

// Settings
extern bool fastModeEnabled;
extern bool verboseLogging;
extern bool manualModeEnabled;
extern int testCountInt;

// Functions
extern void serialMain(void *parameter);

void help();
void fastMode(bool state);
void verbose(bool state);
void manualMode(bool state);
void testCount(int value);
