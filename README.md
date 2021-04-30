# SevSeg

This library turns your Arduino into a seven segment display controller. Use it to easily display numbers on your seven segment display without any additional controllers.

It supports common cathode and common anode displays, and the use of switching transistors. Numbers can be displayed in decimal or hexadecimal representation, with decimal places. Characters can be displayed (as accurately as possible). It also supports multiple displays, of varying dimensions. Shift registers and similar devices are NOT supported.

[Download it from GitHub][1].

Direct any questions or suggestions to deanreading@hotmail.com. If I have the time, I'm happy to help you get things working.

#### Note on shift registers
It's often preferred to drive seven segment displays through shift register chips, as that only uses ~3 micrcontroller pins instead of ~12 pins. This library does not support shift registers. However, there's a mostly-compatible branch that does support shift registers.
See [bridystone's SevSegShift][5].

## Hardware

### Seven segment display pins

Your display should have:
*   **Digit Pins** \- One for each digit. These are the 'common pins'. They will be cathodes (negative pins) for common cathode displays, or anodes (positive pins) for common anode displays.
*   **8 Segment Pins** \- One for each of the seven segments plus the decimal point.


### Arduino connections

All digit pins and segment pins can be connected to any of the Arduino's digital pins, or analog pins with digital support; just make sure you take note of your connections! Analog pins on most Arduinos have digital support, but the Arduino Nano is an exception.


### Current-limiting resistors

Don't forget that the display uses LEDs, so you should use current-limiting resistors in series with the *digit pins*. 330 ohms is a safe value if you're unsure. If you use current-limiting resistors on the *segment pins* instead, then set resistorsOnSegments to true (see the example SevSeg_Counter.ino).


### Hardware configuration

You have to specify your hardware configuration to the library as the first argument in sevseg.begin. The options are detailed below.

#### Simple, low power displays
These displays are powered directly through the Arduino output pins.
*   **COMMON_CATHODE** \- For common cathode displays without switches. These displays require a low voltage at the digit pin to illuminate the digit.
*   **COMMON_ANODE** \- For common anode displays without switches. These displays require a high voltage at the digit pin to illuminate the digit.

#### Displays with switches
Some displays (mostly bigger ones) use switching transistors, but most people won't have to worry about the configurations below.
*   **N_TRANSISTORS** \- If you use N-type transistors to sink current (or any other active-high, low-side switches).
*   **P_TRANSISTORS** \- If you use P-type transistors to supply current (or any other active-low, high-side switches).
*   **NP_COMMMON_CATHODE** \- If your setup uses N-type AND P-type transistors with a common cathode display.
*   **NP_COMMMON_ANODE** \- If your setup uses N-type AND P-type transistors with a common anode display.
Note that use of active-high, high-side switches will have no impact on the configuration chosen. There are usually called high-side switches.


### Example pinout

In the below pinout, digits are numbered 1, 2, 3, 4.
Segments are numbered A through G plus Decimal Point (DP), according to [this picture][2].
Pins are ordered as looking at the front of the display.

[Cheap, 4-digit, 12-pin display from Ebay][3] (labelled HS410561k-32 on bottom edge):
4-digit common anode display, with 2 rows of 6 pins.
```
Top Row:    1 A F  2 3 B
Bottom Row: E D DP C G 4
```

### Sample simulations
The Wokwi team has created sample simulations of the examples in this library:
[Wokwi SevSeg_Counter Example][6].  
[Wokwi stringWithPeriod Example][7].  
[Wokwi testWholeDisplay Example][8].  
 

## Software

To install, copy the SevSeg folder into your arduino sketchbook\-libraries folder. More detailed instructions are [here][4].
The Library Manager can be used from arduino version 1.6.2.


### Setting up

```c++
#include "SevSeg.h"
SevSeg sevseg; //Instantiate a seven segment object

void setup() {
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected. Then, you only need to specify 7 segmentPins[]

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  ...
}
```

`digitPins` is an array that stores the arduino pin numbers that the digits are connected to. Order them from left to right.
`segmentPins` is an array that stores the arduino pin numbers that the segments are connected to. Order them from segment a to g, then the decimal place (if it's connected).
If you wish to use more than 8 digits, increase MAXNUMDIGITS in SevSeg.h.


### Refreshing the display

```c++
sevseg.refreshDisplay();
```

Your program must run the refreshDisplay() function repeatedly to display the number. 
**Warning: Any calls to delay() will interfere with the display.**
Any delays introduced by other functions will produce undesirable effects on the display. If you need help getting away from delay() statements, I recommend the simple [Blink Without Delay][9] arduino example sketch.

To blank the display, call:

```c++
sevseg.blank();
```

### Setting a number
#### Integer
```c++
sevseg.setNumber(3141,3); // Displays '3.141'
```
The first argument is the number to display. The second argument indicates where the decimal place should be, counted from the least significant digit. E.g. to display an integer, the second argument is 0.

#### Floating point
```c++
sevseg.setNumberF(3.14159f,3); //Displays '3.141'
```
Floats are supported. In this case, the second argument indicates how many decimal places of precision you want to display.

Note that:

 - Out of range numbers are shown as '----'. 
 - If the second argument is -1 or omitted, there will be no decimal place. 
 - Enter 'true' as the third argument to display the number in hexadecimal representation (instead of decimal)

### Setting a character string

```c++
sevseg.setChars("abcd");
```

Character arrays can be displayed - as accurately as possible on a seven segment display. See SevSeg.cpp digitCodeMap[] to notes on each character. Only alphanumeric characters, plus ' ', '-', '_', and '.' are supported. The character array should be NULL terminated.

### Custom display setting
```c++
// Set the segments for every digit on the display
uint8_t segs[4] = {0, 0x5B, 0x6D, 0x63};
sevseg.setSegments(segs);
```
```c++
// Set the segments for a single digit. Set digit 3 to 0x63. 
sevseg.setSegmentsDigit(3, 0x63);
```
You can manipulate individual segments if needed. Each byte represents the display of a single digit, with each bit representing a single segment. The bits represent segments in the order .GFEDCBA. See SevSeg.cpp for more examples of these 'digitCodes'.

### Setting the brightness

```c++
sevseg.setBrightness(90);
```

The brightness can be adjusted using a value between -200 and 200. 0 to 100 is the standard range.
Numbers greater than 100 and less than -100 may cause noticeable flickering.
Note that a 0 does not correspond to no brightness - nor does -200. If your display has noticeable flickering, modifying the brightness towards 0 may correct it.
Results will vary for each implementation. The brightness seen depends on the display characteristics, the arduino model driving it, the resistors used, and the amount of time spent doing other things in the program.

## License

MIT License

Copyright (c) 2020 Dean Reading

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

[1]: https://github.com/DeanIsMe/SevSeg
[2]: https://en.wikipedia.org/wiki/File:7_segment_display_labeled.svg
[3]: http://www.ebay.com/sch/i.html?LH_BIN=1&_from=R40&_sacat=0&_nkw=7+segment+display+4+digit+2+pcs&_sop=15
[4]: http://arduino.cc/en/Guide/Libraries
[5]: https://github.com/bridystone/SevSegShift
[6]: https://wokwi.com/arduino/libraries/SevSeg/SevSeg_Counter
[7]: https://wokwi.com/arduino/libraries/SevSeg/stringWithPeriod
[8]: https://wokwi.com/arduino/libraries/SevSeg/testWholeDisplay
[9]: https://www.arduino.cc/en/Tutorial/BuiltInExamples/BlinkWithoutDelay