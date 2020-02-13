#pragma once

#include <SevSeg.h>

class SevSegShift: public SevSeg {
public:
  /* Constructor
    pinDS => Data Select PIN
    pinSHCP => pin for ShiftClock
    pinSTCP => pin for StoreClock
    registerCount => number of used shift registers (currently set to 2 - later maybe differently)*/
  SevSegShift(
    byte pinDS, 
    byte pinSHCP, 
    byte pinSTCP,
    const byte numberOfShiftRegisters = 2 // currently const value (not changeable) - maybe in future
  );

  /*
    prepare the SevenSeg-Shift-Register lib
    hardwareConfig -> ANODE or CATHODE SevensSegment
    numDigits -> number of digitSegments
    byte shiftRegisterMapDigits[], -> pins are here the OUTPUT PINs of the Shift Register
    byte shiftRegisterMapSegments[], -> pins are here the OUTPUT PINs of the Shift Register
    resOnSegments -> Resistors on Segments instead of on LED (as it should be)
    upDataWithDelays -> ?
    leadingZeros -> use leading zeros
    disableDecPoint -> is the Decimal point *not available? */
  void begin(byte hardwareConfig, 
    byte numDigitsIn,
    byte shiftRegisterMapDigits[],
    byte shiftRegisterMapSegments[],
    bool resOnSegmentsIn=false, 
    bool updateWithDelaysIn=false, 
    bool leadingZerosIn=false,
    bool disableDecPoint=false
  );
protected:
  virtual void segmentOn(byte segmentNum);
  virtual void segmentOff(byte segmentNum);
  virtual void digitOn(byte digitNum);
  virtual void digitOff(byte digitNum);

  /*
    pushing the data in _shiftRegisterMap to all the Shift Registers
    */
  void pushData2ShiftRegister();

private:
  byte _pinDS;
  byte _pinSHCP;
  byte _pinSTCP;

  // which ports of the Shift Registers are used for which purpose
  byte *_shiftRegisterMapDigits;
  byte *_shiftRegisterMapSegments;

  // store number of ShiftRegisters
  byte _numberOfShiftRegisters;
  // current shift register map (to be used to cycle through when pushing data to the register)
  byte *_shiftRegisterMap;
};