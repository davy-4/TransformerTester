#pragma once
#include <Arduino.h>
#include <vector>
#include <string>

class test {
  public:
    // Variables for tester
    static bool testLock;

    // Functions
    static void startTest();
    static void testMain(void *parameter);

  private:
    static bool testTrigger;
};