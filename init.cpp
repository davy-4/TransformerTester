#include <Arduino_FreeRTOS.h>
#include "init.h"

static long init::start;
static long init::current;

void init::initialize() {
  init::start = millis();
};