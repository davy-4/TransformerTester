#include <FastLED.h>

#include "init.h"
#include "serial.h"
#include "compute.h"
#include "test.h"

TaskHandle_t SerialHandle = nullptr;
TaskHandle_t TestHandle = nullptr;

void setup() {
  Serial.begin(115200);
  init::initialize();
  xTaskCreatePinnedToCore(serial::serialMain, "Serial", 10000, nullptr, 1, &SerialHandle, 1);
  xTaskCreatePinnedToCore(test::testMain, "Testing", 10000, nullptr, 0, &TestHandle, 1);
}

void loop() {
  // use FreeRTOS tasks
}
