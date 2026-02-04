// TTL implementation prototype
#include <Arduino_FreeRTOS.h> // double include?
#include "serial.h"
#include "compute.h"

// defaults
bool fastModeEnabled = false;
bool verboseLogging = false;
bool manualModeEnabled = false;
int testCountInt = 3;

enum SettingType {BOOL,INT};

struct Command {
  const char* name;
  void (*function)(const String&);
  const char* description;
  const char* usage;
};

struct Setting {
  const char* name;
  SettingType type;
  void* value;
  const char* description;
};

// dynamic settings list
Setting settings[] = { // setting, datatype, variable, description
  {"fastmode", BOOL, &fastModeEnabled, "No clue"},
  {"verbose",  BOOL, &verboseLogging, "Verbose debug logging"},
  {"manual",   BOOL, &manualModeEnabled, "Manually test the IC via command"},
  {"testcount", INT, &testCountInt, "Number of tests to run per IC"}, // might be useless
};

Command commands[] = { // command, function, description, usage
  {"test", serial::placeholder, "Execute this command to test the IC", "test"},
  {"help", serial::help, "Show this help table", "help"},
  {"set", serial::set, "Change the settings of the tester", "set <setting> <value>"},
};
const int commandCount = sizeof(commands) / sizeof(commands[0]);

// helper function to pad text in tables, e.g., help table
void printPadded(const String& text, size_t width, const String& padding) { // printPadded("text", 6, "#"); will print "text##"
  Serial.print(text);
  if (text.length() < width) {
    for (size_t i = 0; i < width - text.length(); i++) {
      Serial.print(padding);
    }
  }
}

void serial::serialMain(void *parameter) {
  while (true) {
    if (Serial.available()) {
      String input = Serial.readStringUntil('\n'); input.trim();  // clean whitespace
      Serial.print("~/");
      Serial.println(input); // echo the command
      if (input.length() == 0)
        continue;

        int firstSpace = input.indexOf(' ');
        String cmd = (firstSpace == -1) ? input : input.substring(0, firstSpace);

        bool matched = false;

        for (int i = 0; i < commandCount; i++) {
          if (cmd.equalsIgnoreCase(commands[i].name)) {
            commands[i].function(input);     // execute command
            matched = true;
            break;
          }
        }
      if (matched == false) { // autocomplete typos
        int assumedDist = 0xff; // any big number
        String assumedCmd = "";

        for (int i = 0; i < commandCount; i++) {
          int d = compute::levenshtein(cmd, commands[i].name);
            if (d < assumedDist) {
              assumedDist = d;
              assumedCmd = commands[i].name;
            }
          }

          if (assumedDist <= 2) {   // format off linux, "Command not found: x, did you mean xy?"
            Serial.print("Command not found: ");
            Serial.print(cmd);
            Serial.print(", did you mean: ");
            Serial.print(assumedCmd);
            Serial.println("?");
          } else { // "Command not found: x, type 'help' for a list of commands."
            Serial.print("Command not found: ");
            Serial.print(cmd);
            Serial.println(", type 'help' for a list of commands.");
          }

      }
    }
    vTaskDelay(1);  // yield
  }
}

void serial::help() {
  const size_t columnWidth = 12; // pad the setting column
  const size_t columnWidthSecondary = 5; // pads the value column

  Serial.println("--- Commands ---");
  for (size_t i = 0; i < sizeof(commands)/sizeof(Command); i++) {
    printPadded(commands[i].name, columnWidth, " ");
    Serial.print(" | ");
    Serial.println(commands[i].description);
  }

  Serial.println();
  Serial.println("--- Settings ---");
  Serial.println("Usage: set [setting] (value)\n");

  printPadded("setting", columnWidth, " ");
  Serial.print(" | ");
  printPadded("value", columnWidthSecondary, " ");
  Serial.println(" | description");
  Serial.println("-------------|-------|---------------------------------------------");

  for (size_t i = 0; i < sizeof(settings)/sizeof(Setting); i++) {
    printPadded(settings[i].name, columnWidth, " ");
    Serial.print(" | ");

    String valueStr;
    if (settings[i].type == BOOL) {
      bool val = *(bool*)settings[i].value;
      valueStr = val ? "true" : "false";
    } else if (settings[i].type == INT) {
      int val = *(int*)settings[i].value;
      valueStr = String(val);
    }

    printPadded(valueStr, columnWidthSecondary, " ");
    Serial.print(" | ");

    // description
    Serial.println(settings[i].description);
  }
}


void serial::set(String input) {
  String arg = input.substring(4);
  int seperator = arg.indexOf(' ');
  if (seperator < 0) {
    Serial.println("Usage: <setting> <value>");
  }
  String key = arg.substring(0, seperator);
  String value = arg.substring(seperator + 1);

  Serial.println(key);
  Serial.println(value);
}

void serial::placeholder(const String& input) {} // function placeholder
