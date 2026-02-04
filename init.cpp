#include <Arduino_FreeRTOS.h>
#include "init.h"

long init::start;
long init::current;

void init::initialize() {
  Serial.println("start millis");
  init::start = millis();
  Serial.println("got millis!!");
};