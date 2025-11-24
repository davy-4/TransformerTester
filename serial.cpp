// TTL implementation prototype
#include "serial.h"

// defaults
bool fastModeEnabled = false;
bool verboseLogging = false;
bool manualModeEnabled = false;
int testCountInt = 3;

enum SettingType {BOOL,INT};

struct Command {
  const char* name;
  const char* description;
};

struct Setting {
  const char* name;
  SettingType type;
  void* value;
  const char* description;
};

// dynamic settings and commands list
Setting settings[] = {
  {"fastmode", BOOL, &fastModeEnabled, "No clue"},
  {"verbose",  BOOL, &verboseLogging, "Verbose debug logging"},
  {"manual",   BOOL, &manualModeEnabled, "Manually test the IC via command"},
  {"testcount", INT, &testCountInt, "Number of tests to run per IC"}, // might be useless
};

Command commands[] = {
  {"test", "Execute this command to test the IC"},
};

void serialMain(void *parameter) { // freeRTOS demands a parameter
  while (!Serial){
    if (verboseLogging==true) {Serial.println("serial connected!");}

    if (Serial.read() == "help") {
      help();
    } else if (Serial.read() == "set ") { // <-- heads up there is a space here
      //  oh no
      /*  scan for set, go past the space after "set "get the word by going through each letter until we get a space?
       *  then check whether the letters correlate to a function.
       *  check if the function is an int or bool.
       *  if bool, scan the word till we get a \n? might be wrong
       *  if int, count letters until we get \n
       */
    }
  }
}


void help() {
  Serial.println("--- Commands ---");
  for (size_t i = 0; i < sizeof(commands)/sizeof(Command); i++) {
    Serial.println(commands[i].name);
    Serial.print("Description: ");
    Serial.println(commands[i].description);
  }
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

void fastMode(bool state) { fastModeEnabled = state;
  // do tests faster
}

void verbose(bool state) { verboseLogging = state;
  // all we have to do is just check if this is enabled in the main loop
}

void manualMode(bool state) { manualModeEnabled = state;
  // command test only; or button press
}

void testCount(int value) { testCountInt = value;
  // do multiple tests; check if any of them failed; could false positive though
}
