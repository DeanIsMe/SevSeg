SevSeg
======
 Copyright 2016 Dean Reading

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
* * *

This library turns your Arduino into a seven segment display controller! Use it to easily display numbers on your seven segment display without any additional controllers.

It supports common cathode and common anode displays, and the use of switching transistors. Numbers can be displayed in decimal or hexadecimal representation, with decimal places. Characters can be displayed (as accurately as possible). It also supports multiple displays, of varying dimensions. Shift registers and similar devices are NOT supported.

[Download it from GitHub][1].

Direct any questions or suggestions to deanreading@hotmail.com. If I have the time, I'm happy to help you get things working.

#### Update Version 3.3.0 (February 2017)

 Added the ability to keep leading zeros. This is now an extra
 parameter in the begin() function.
 
#### Update Version 3.2.0 (December 2016)

 Backwards compatible with version 3.1  
 Updated to Arduino 1.5 Library Specification  
 New display function - no longer consumes processor time with delay()  
 Now supports hexadecimal number printing  
 The decimal point can now be omitted with a negative decPlaces   
 Alphanumeric strings can be displayed (inaccurately) with setChars   
 Removed #define RESISTORS_ON_SEGMENTS. Now a begin() input   
 Can now blank() the display   
 Now 'heavier' - uses more PROGMEM and RAM  


* * *

### HARDWARE

#### Seven Segment Display Pins

Your display should have:  
**Digit Pins** \- One for each digit. These are the 'common pins'. They will be cathodes (negative pins) for common cathode displays, or anodes (positive pins) for common anode displays.  
**8 Segment Pins** \- One for each of the seven segments plus the decimal point.


#### Arduino Connections

All digit pins and segment pins can be connected to any of the Arduino's digital or analog pins; just make sure you take note of your connections!


#### Current-limiting Resistors

Don't forget that the display uses LEDs, so you should use current-limiting resistors in series with the *digit pins*. 330 ohms is a safe value if you're unsure. If you use current-limiting resistors on the *segment pins* instead, then set resistorsOnSegments to true (see the example SevSeg_Counter.ino).

#### Hardware Configuration

You have to specify your hardware configuration to the library as the first argument in sevseg.begin. The options are detailed below.

##### Simple, Low Power Displays  
These displays are powered directly through the Arduino output pins.  
  * **COMMON_CATHODE** \- For common cathode displays without switches. These displays require a low voltage at the digit pin to illuminate the digit.  
  * **COMMON_ANODE** \- For common anode displays without switches. These displays require a high voltage at the digit pin to illuminate the digit.

##### Displays with Switches  
Some displays (mostly bigger ones) use switching transistors, but most people won't have to worry about the configurations below.  
  * **N_TRANSISTORS** \- If you use N-type transistors to sink current (or any other active-high, low-side switches).  
  * **P_TRANSISTORS** \- If you use P-type transistors to supply current (or any other active-low, high-side switches).  
  * **NP_COMMMON_CATHODE** \- If your setup uses N-type AND P-type transistors with a common cathode display.  
  * **NP_COMMMON_ANODE** \- If your setup uses N-type AND P-type transistors with a common anode display.  
Note that use of active-high, high-side switches will have no impact on the configuration chosen. There are usually called high-side switches.

#### Example Pinout 

In the below pinout, digits are numbered 1, 2, 3, 4.
Segments are numbered A through G plus Decimal Point (DP), according to [this picture][4].
Pins are ordered as looking at the front of the display.

[Cheap, 4-digit, 12-pin display from Ebay][5] (labelled HS410561k-32 on bottom edge):  
4-digit common anode display, with 2 rows of 6 pins.
```
Top Row:    1 A F  2 3 B  
Bottom Row: E D DP C G 4  
```

* * *

### SOFTWARE

To install, copy the SevSeg folder into your arduino sketchbook\-libraries folder. More detailed instructions are [here][3].
The Library Manager can be used from arduino version 1.6.2.


#### Setting Up


     #include "SevSeg.h"
     SevSeg sevseg; //Instantiate a seven segment object

    void setup() {
       byte numDigits = 4;   
       byte digitPins[] = {2, 3, 4, 5};
       byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
       bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
       byte hardwareConfig = COMMON_ANODE; // See README.md for options
       sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
       ...


digitPins is an array that stores the arduino pin numbers that the digits are connected to. Order them from left to right.
segmentPins is an array that stores the arduino pin numbers that the segments are connected to. Order them from segment a to g , then the decimal place.
If you wish to use more than 8 digits, increase MAXNUMDIGITS in SevSeg.h.


#### Setting a Number


     sevseg.setNumber(3141,3); // Displays '3.141'


The first argument is the number to display. The second argument indicates where the decimal place should be, counted from the least significant digit. E.g. to display an integer, the second argument is 0.  
Floats are supported. In this case, the second argument indicates how many decimal places of precision you want to display. E.g:


     sevseg.setNumber(3.14159f,3); //Displays '3.141'


Out of range numbers are shown as '----'.

If the second argument is -1 or omitted, there will be no decimal place.

Enter 'true' as the third agument to display the number in hexadecimal representation.

#### Setting a Character String


     sevseg.setChars("abcd");

Character arrays can be displayed - as accurately as possible on a seven segment display. See SevSeg.cpp digitCodeMap[] to notes on each character. Only alphanumeric characters, plus ' ' and '-' are supported. The character array should be NULL terminated.


#### Displaying


     sevseg.refreshDisplay();


Your program must run the refreshDisplay() function repeatedly to display the number. Note that any delays introduced by other functions will produce undesirable effects on the display.

To blank the display, call:

     sevseg.blank();



#### Setting the Brightness


     sevseg.setBrightness(90);


The brightness can be adjusted using a value between 0 and 100.  
Note that a 0 does not correspond to no brightness. If your display has noticeable flickering, reducing the brightness level may correct it.

[1]: https://github.com/DeanIsMe/SevSeg
[2]: https://docs.google.com/file/d/0Bwrp4uluZCpNdE9oWTY0M3BncTA/edit?usp=sharing
[3]: http://arduino.cc/en/Guide/Libraries
[4]: https://en.wikipedia.org/wiki/File:7_segment_display_labeled.svg
[5]: http://www.ebay.com/sch/i.html?LH_BIN=1&_from=R40&_sacat=0&_nkw=7+segment+display+4+digit+2+pcs&_sop=15
  
