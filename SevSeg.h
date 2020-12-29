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
  void begin(byte hardwareConfig, byte numDigitsIn, const byte digitPinsIn[],
          const byte segmentPinsIn[], bool resOnSegmentsIn=0, 
          bool updateWithDelaysIn=0, bool leadingZerosIn=0,
		  bool disableDecPoint=0);
  void setBrightness(int brightnessIn); // A number from 0..100

  void setNumber(long numToShow, char decPlaces=-1, bool hex=0);
  void setNumber(unsigned long numToShow, char decPlaces=-1, bool hex=0);
  void setNumber(int numToShow, char decPlaces=-1, bool hex=0);
  void setNumber(unsigned int numToShow, char decPlaces=-1, bool hex=0);
  void setNumber(char numToShow, char decPlaces=-1, bool hex=0);
  void setNumber(byte numToShow, char decPlaces=-1, bool hex=0);
  void setNumber(float numToShow, char decPlaces=-1, bool hex=0);

  void setSegments(const byte segs[]);
  void getSegments(byte segs[]);
  void setChars(const char str[]);
  void blank(void);

private:
  void setNewNum(long numToShow, char decPlaces, bool hex=0);
  void findDigits(long numToShow, char decPlaces, bool hex, byte digits[]);
  void setDigitCodes(const byte nums[], char decPlaces);
  void segmentOn(byte segmentNum);
  void segmentOff(byte segmentNum);
  void digitOn(byte digitNum);
  void digitOff(byte digitNum);

  byte digitOnVal,digitOffVal,segmentOnVal,segmentOffVal;
  bool resOnSegments, updateWithDelays, leadingZeros;
  byte digitPins[MAXNUMDIGITS];
  byte segmentPins[8];
  byte numDigits;
  byte numSegments;
  byte prevUpdateIdx; // The previously updated segment or digit
  byte digitCodes[MAXNUMDIGITS]; // The active setting of each segment of each digit
  unsigned long prevUpdateTime; // The time (millis()) when the display was last updated
  int ledOnTime; // The time (us) to wait with LEDs on
  int waitOffTime; // The time (us) to wait with LEDs off
  bool waitOffActive; // Whether  the program is waiting with LEDs off
};

#endif //SevSeg_h
/// END ///
