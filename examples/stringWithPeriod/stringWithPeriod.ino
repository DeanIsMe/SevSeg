/*
 Displaying a string that contains a period on a seven-segment display.

 Contributed by Matthew Nielsen (github.com/xunker) for the SevSeg Arduino
 Library (github.com/DeanIsMe/SevSeg) by Dean Reading.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

 */

#include "SevSeg.h"
SevSeg sevseg; //Instantiate a seven segment controller object

#define MAX_NUMBER_STRINGS 12
#define MAX_STRING_SIZE 8
char testStrings[MAX_NUMBER_STRINGS][MAX_STRING_SIZE];

#define PATTERN_CHANGE_TIME 1000
unsigned long timer = millis() - PATTERN_CHANGE_TIME;
byte testStringsPos = 0;

void setup() {
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  bool updateWithDelays = false; // Default. Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
  sevseg.setBrightness(90);

  // Adds set of test strings with periods in various places
  strcpy(testStrings[0], "A..BC.");
  strcpy(testStrings[1], "....");
  strcpy(testStrings[2], ".   ");
  strcpy(testStrings[3], " .  ");
  strcpy(testStrings[4], "  . ");
  strcpy(testStrings[5], "   .");
  strcpy(testStrings[6], ".ABC");
  strcpy(testStrings[7], "A.BCD");
  strcpy(testStrings[8], "A.B.CD");
  strcpy(testStrings[9], "A.B.C.D");
  strcpy(testStrings[10], "A.B.C.D.");
  strcpy(testStrings[11], ". . . .");
}

void loop() {

  // Cycle to the next string every one second
  if (millis() > (timer + PATTERN_CHANGE_TIME)) {
    sevseg.setChars(testStrings[testStringsPos]);
    testStringsPos++;
    if (testStringsPos >= MAX_NUMBER_STRINGS) testStringsPos = 0;
    timer = millis();
  }

  sevseg.refreshDisplay(); // Must run repeatedly
}

/// END ///
