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

#include "init.h"
#include "serial.h"
#include "compute.h"

TaskHandle_t SerialHandle = NULL;

void setup() {
  Serial.begin(115200);
  init::initialize();

  // heads up, 3rd arg is in words, not bytes
  xTaskCreate(serial::serialMain, "Serial", 256, NULL, 1, &SerialHandle);
  vTaskStartScheduler();
}

void loop() {
  // use FreeRTOS tasks
}
