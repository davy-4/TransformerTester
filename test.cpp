#include "test.h"
#include <Arduino.h>
#include <vector>
#include <string>

#define p1 37
#define p2 38
#define p3 39
#define p4 40
#define p5 41
#define p6 42

bool test::testLock = 0;
bool test::testTrigger = 0; // protected!!!

std::vector<String> failed;

void test::startTest() {
  if (testLock == 0) {
    static bool testTrigger = 1;
  } else {
    if (Serial.available()) {
      Serial.println("Denied, task is locked");
    }
  }
}

int check(int in, int out) { // in-out format, +, -
  register bool temp = 0;
  pinMode(out, OUTPUT); 
  digitalWrite(out, LOW);
  pinMode(in, INPUT_PULLUP); 
  delay(2);
  temp = !digitalRead(in);
  pinMode(out, INPUT); // release pin

  if (temp == 0) {
    failed.push_back(String(in)); 
    failed.push_back(String(out));
    };
  return temp;
}

void test::testMain(void *parameter) {
  pinMode(p1, INPUT);
  pinMode(p2, INPUT);
  pinMode(p3, INPUT);
  pinMode(p4, INPUT);
  pinMode(p5, INPUT);
  pinMode(p6, INPUT);
  for (;;) {
    Serial.println("s1");
    if (testTrigger == 1) {
      Serial.println("s1");
      testTrigger == 0;
      if (testLock == 0) {
        Serial.println("s2");
        testLock == 1;
        // -- extensive test
        /* Test 1: 1-2 */ check(p1,p2);
        /* Test 2: 1-3 */ check(p1,p3);
        /* Test 3: 2-3 */ check(p2,p3);

        /* Test 4: 4-5 */ check(p4,p5);
        /* Test 5: 4-6 */ check(p4,p6);
        /* Test 6: 5-6 */ check(p5,p6);

        /* Test 7: 1-4 */ check(p1,p4);
        /* Test 8: 1-5 */ check(p1,p5);
        /* Test 9: 1-6 */ check(p1,p6);

        /* Test 10: 2-4 */ check(p2,p4);
        /* Test 11: 2-5 */ check(p2,p5);
        /* Test 12: 2-6 */ check(p2,p6);

        /* Test 13: 3-4 */ check(p3,p4);
        /* Test 14: 3-5 */ check(p3,p5);
        /* Test 15: 3-6 */ check(p3,p6);

        if (failed.empty()) {
          Serial.println("PASS!");
        } else {
          Serial.print("FAIL:");
          for(const String& s : failed) {
            Serial.print(" ");
            Serial.print(s);
          }
        }
        testLock == 0;
      } else {
        if (Serial.available()) {
          Serial.println("Denied, task is locked");
        }
      }
    } else {
      vTaskDelay(100 / portTICK_PERIOD_MS);
    }
  }
}