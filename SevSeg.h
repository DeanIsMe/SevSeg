/* SevSeg Library
 
 Copyright 2017 Dean Reading
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 
 
 This library allows an Arduino to easily display numbers in decimal format on
 a 7-segment display without a separate 7-segment display controller.
 
 Direct any questions or suggestions to deanreading@hotmail.com
 See the included readme for instructions.
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
  void begin(byte hardwareConfig, byte numDigitsIn, byte digitPinsIn[],
          byte segmentPinsIn[], bool resOnSegmentsIn=0, 
          bool updateWithDelaysIn=0, bool leadingZerosIn=0);
  void setBrightness(int brightnessIn); // A number from 0..100

  void setNumber(long numToShow, char decPlaces=-1, bool hex=0);
  void setNumber(unsigned long numToShow, char decPlaces=-1, bool hex=0);
  void setNumber(int numToShow, char decPlaces=-1, bool hex=0);
  void setNumber(unsigned int numToShow, char decPlaces=-1, bool hex=0);
  void setNumber(char numToShow, char decPlaces=-1, bool hex=0);
  void setNumber(byte numToShow, char decPlaces=-1, bool hex=0);
  void setNumber(float numToShow, char decPlaces=-1, bool hex=0);

  void setSegments(byte segs[]);
  void setChars(char str[]);
  void blank(void);

private:
  void setNewNum(long numToShow, char decPlaces, bool hex=0);
  void findDigits(long numToShow, char decPlaces, bool hex, byte digits[]);
  void setDigitCodes(byte nums[], char decPlaces);

  bool digitOn,digitOff,segmentOn,segmentOff;
  bool resOnSegments, updateWithDelays, leadingZeros;
  byte digitPins[MAXNUMDIGITS];
  byte segmentPins[8];
  byte numDigits;
  byte prevUpdateIdx;
  byte digitCodes[MAXNUMDIGITS];
  int ledOnTime;
  unsigned long prevUpdateTime;
};

#endif //SevSeg_h
/// END ///
