#include "serial.h"

// defaults
bool fastModeEnabled = false;
bool verboseLogging = false;
bool manualModeEnabled = false;
int testCountInt = 3;

enum SettingType {BOOL,INT};

struct Setting {
  const char* name;
  SettingType type;
  void* value;
  const char* description;
};

// dynamic settings list
Setting settings[] = {
    {"fastmode", BOOL, &fastModeEnabled, "No clue"},
    {"verbose",  BOOL, &verboseLogging, "Verbose debug logging"},
    {"manual",   BOOL, &manualModeEnabled, "Manually test the IC via command"},
    {"testcount", INT, &testCountInt, "Number of tests to run per IC"} // would this increase false positive chance?
};

void help() { // I haven't tested whether this compiles yet
    Serial.println("--- Settings ---");
    Serial.println("Usage: set [setting] value");
    Serial.println("Hint: Current settings are displayed");

    for (size_t i = 0; i < sizeof(settings)/sizeof(Setting); i++) {
        Serial.print(settings[i].name);
        Serial.print(" ");
        if (settings[i].type == BOOL) {
            bool val = *(bool*)settings[i].value;
            Serial.println(val ? "true" : "false");

        } else if (settings[i].type == INT) {
            int val = *(int*)settings[i].value;
            Serial.println(val);
        }

        Serial.print("Description: ");
        Serial.println(settings[i].description);
    }
}

void fastMode(bool state) {
  fastModeEnabled = state;
  // do tests faster
}

void verbose(bool state) {
  verboseLogging = state;
  // all we have to do is just check if this is enabled in the main loop
}

void manualMode(bool state) {
  manualModeEnabled = state;
  // command test only; or button press
}

void testCount(int value) {
  testCountInt = value;
  // do multiple tests; check if any of them failed; could false positive though
}
