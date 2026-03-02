#include <FastLED.h>
#include "init.h"

// pins in p# format

// LED pin
#define ledPin 48

#define NUM_LEDS 1
CRGB leds[NUM_LEDS];

long init::start;
long init::current;

bool btnLock = 0;

int init::ledBrightness = 200; // 0-255 control
bool init::ledLock = 0;



void init::initialize() {
  init::start = millis();
};