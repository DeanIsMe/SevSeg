/* SevSeg testDisplay
 
 Copyright 2023 Dean Reading
 
 This example is helpful to test a display by cycling through each segment,
 then each digit.

 You can simulate this sketch on Wokwi
 https://wokwi.com/projects/371856060223388673
 */

#include <SevSeg.h>

void nextState(); // Forward declaration of function

SevSeg sevseg; // Instantiate a seven segment object
uint8_t state = 0;
uint8_t numDigits;
const uint32_t INTERVAL_MS = 500; // The time spent in each state

// setup
/******************************************************************************/
void setup() {
  numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected. Then, you only need to specify 7 segmentPins[]

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);

  Serial.println("SevSeg testDisplay.ino");
  Serial.println("This sketch will cycle through all segments, then all digits");
  Serial.println("2023 Dean Reading");
  Serial.begin(115200);
}

// loop
/******************************************************************************/
void loop() {
  static unsigned long timer = millis();
  
  if (millis() - timer >= INTERVAL_MS) {
    timer = millis();
    nextState();
  }

  sevseg.refreshDisplay(); // Must run repeatedly
}

// nextState
/******************************************************************************/
void nextState() {

    switch (state) {
        // CYCLE SEGMENTS
        case 0:
            Serial.println("\nCycling through each segment");
            sevseg.blank();
        break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        {
            // Set a single segment on (for all digits)
            uint8_t segNum = (state - 1);
            uint8_t segVal = 1 << segNum;
            for (int d=0; d < numDigits; d++) {
                sevseg.setSegmentsDigit(d, segVal);
            }
            Serial.print("Segment "); Serial.println(char('a' + segNum));
            break;
        }

        // CYCLE DIGITS
        case 9:
            Serial.println("Cycling through each digit");
            sevseg.blank();
        break;
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        {
            // Set 1 digit on (all segments)
            uint8_t digitNumOn = state - 10;
            sevseg.blank();
            sevseg.setSegmentsDigit(digitNumOn, 0xFF);
            Serial.print("Digit "); Serial.print(digitNumOn); Serial.println(" on");
            
            if (digitNumOn + 1 == numDigits) {
                state = 20 - 1; // This is the last digit. Jump to state 20
            }
            break;
        }

        // ALL ON
        case 20: // Wait 1 step
            sevseg.blank();
        break;
        case 21:
            for (int d=0; d < numDigits; d++) {
                sevseg.setSegmentsDigit(d, 0xFF);
            }
            Serial.println("All LEDs on!");
        break;

        case 22: // Wait 2 steps
            Serial.println("Cycle finished");
        case 23:
            sevseg.blank();
        break;

        default:
            state = -1; // Should never arrive here
            break;
    }

    state++;
    if (state > 23) {
        state = 0;
    }
}

/// END ///