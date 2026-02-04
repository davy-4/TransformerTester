/*  UNO R3 specs
 *  
 *  GPIO, UART, I2C, SPI, PWM, ADC
 *  5v 20mA per I/O pin
 *  8-bit AVR 16mhz
 *  2KB SRAM, 32KB FLASH, 1kb EEPROM
 *  in kilobytes, 
 * 
 *  optimization-specific info
 *  16,000,000 instructions per second, 62.5ns per instruction
 *  latency target is 10ms, 10/0.0000625 = 160,000 instructions per sec
 *  
 *  list of functions and instructions used
 *  digitalWrite() = ~50-60
 *  digitalRead() = ~50
 */

#include <Arduino.h>
#include <Arduino_FreeRTOS.h> // install FreeRTOS by Richard Barry in library manager

// display related drivers:
//#include <Wire.h>
//#include <Adafruit_GFX.h> // requirement for the SH1106 driver
//#include <Adafruit_SH110X.h> // the display is a SH1106 128x64 located at 0x3C

#include "init.h"
#include "serial.h"
#include "compute.h"
//#include "display.h"

TaskHandle_t SerialHandle = NULL;
//TaskHandle_t DisplayHandle = NULL;

void setup() {
  Serial.begin(115200);
  //init::initialize();

  // heads up, 3rd arg is in words, not bytes
  xTaskCreate(serial::serialMain, "Serial", 256, NULL, 2, &SerialHandle);
  //xTaskCreate(display::displayMain, "Display", 192, nullptr, 1, &DisplayHandle);
  vTaskStartScheduler();
}

void loop() {
  // use FreeRTOS tasks
}
