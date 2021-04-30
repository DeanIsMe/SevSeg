/* SevSeg Library
 *
 * Copyright 2020 Dean Reading
 *
 * This library allows an Arduino to easily display numbers and letters on a
 * 7-segment display without a separate 7-segment display controller.
 *
 * See the included readme for instructions.
 * https://github.com/DeanIsMe/SevSeg
 */

#ifndef MAXNUMDIGITS
#define MAXNUMDIGITS 8 // Can be increased, but the max number is 2^31
#endif

#ifndef SevSeg_h
#define SevSeg_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// Use defines to link the hardware configurations to the correct numbers
#define COMMON_CATHODE 0
#define COMMON_ANODE 1
#define N_TRANSISTORS 2
#define P_TRANSISTORS 3
#define NP_COMMON_CATHODE 1
#define NP_COMMON_ANODE 0


class SevSeg
{
public:
  SevSeg();

  void refreshDisplay();
  void begin(uint8_t hardwareConfig, uint8_t numDigitsIn, const uint8_t digitPinsIn[],
          const uint8_t segmentPinsIn[], bool resOnSegmentsIn=0, 
          bool updateWithDelaysIn=0, bool leadingZerosIn=0,
		  bool disableDecPoint=0);
  void setBrightness(int16_t brightnessIn); // A number from 0..100

  void setNumber(int32_t numToShow, int8_t decPlaces=-1, bool hex=0);
  void setNumberF(float numToShow, int8_t decPlaces=-1, bool hex=0);

  void setSegments(const uint8_t segs[]);
  void getSegments(uint8_t segs[]);
  void setSegmentsDigit(const uint8_t digitNum, const uint8_t segs);
  void setChars(const char str[]);
  void blank(void);

private:
  void setNewNum(int32_t numToShow, int8_t decPlaces, bool hex=0);
  void findDigits(int32_t numToShow, int8_t decPlaces, bool hex, uint8_t digits[]);
  void setDigitCodes(const uint8_t nums[], int8_t decPlaces);
  void segmentOn(uint8_t segmentNum);
  void segmentOff(uint8_t segmentNum);
  void digitOn(uint8_t digitNum);
  void digitOff(uint8_t digitNum);

  uint8_t digitOnVal,digitOffVal,segmentOnVal,segmentOffVal;
  bool resOnSegments, updateWithDelays, leadingZeros;
  uint8_t digitPins[MAXNUMDIGITS];
  uint8_t segmentPins[8];
  uint8_t numDigits;
  uint8_t numSegments;
  uint8_t prevUpdateIdx; // The previously updated segment or digit
  uint8_t digitCodes[MAXNUMDIGITS]; // The active setting of each segment of each digit
  uint32_t prevUpdateTime; // The time (millis()) when the display was last updated
  int16_t ledOnTime; // The time (us) to wait with LEDs on
  int16_t waitOffTime; // The time (us) to wait with LEDs off
  bool waitOffActive; // Whether  the program is waiting with LEDs off
};

#endif //SevSeg_h
/// END ///
