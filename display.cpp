#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Arduino_FreeRTOS.h>
#include "display.h"

//display mock-up

Adafruit_SH1106G display::oled = Adafruit_SH1106G(128, 64, &Wire, -1); // 128x64, rst pin is -1 (same as uno's)

void testdrawchar(void) {
  display::oled.setTextSize(1);
  display::oled.setTextColor(SH110X_WHITE);
  display::oled.setCursor(0, 0);

  for (uint8_t i = 0; i < 168; i++) {
    if (i == '\n') continue;
    display::oled.write(i);
    if ((i > 0) && (i % 21 == 0))
      display::oled.println();
  }
  display::oled.display();
};

void display::displayMain(void *parameter) {
  display::oled.begin(0x3c, true);
  display::oled.clearDisplay();
  display::oled.display();

  for (;;) {
    testdrawchar();
    vTaskDelay(pdMS_TO_TICKS(2000));
    display::oled.clearDisplay();
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}