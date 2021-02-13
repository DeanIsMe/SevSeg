# Change Log

## [3.6.0](https://github.com/DeanIsMe/SevSeg/releases/tag/v3.6.0) (2021-02-13)
*   changed all data types to stdint.h types for better compatibility
*   removed floating point support from setNumber(). 
*   added new function to set a floating point number: setNumberF()

## [3.5.0](https://github.com/DeanIsMe/SevSeg/releases/tag/v3.5.0) (2020-12-28)
*   better compatibility with different boards & platforms
*   getSegments() function
*   added underscore
*   differentiated 'I' and '1'


## [3.4.0](https://github.com/DeanIsMe/SevSeg/releases/tag/v3.4.0) (2019-04-21)

### Added
*   support for '*', which is displayed as degree symbol
*   expanded setBrightness capabilities
*   support for displays with no decimal point
*   improved blank() functionality

## [3.3.0](https://github.com/DeanIsMe/SevSeg/releases/tag/v3.3.0) (2017-02-22)

### Added
*   added the ability to keep leading zeros


## [3.2.0](https://github.com/DeanIsMe/SevSeg/releases/tag/v3.2.0) (2016-12-19)

### Added
*   new display function - no longer consumes processor time with `delay()`
*   now supports hexadecimal number printing
*   the decimal point can now be omitted with a negative `decPlaces`
*   alphanumeric strings can be displayed (inaccurately) with `setChars()`
*   can now `blank()` the display

### Changed
*   updated to Arduino 1.5 Library Specification
*   removed `#define RESISTORS_ON_SEGMENTS`
*   now **heavier** - uses more PROGMEM and RAM


## [3.1](https://github.com/DeanIsMe/SevSeg/releases/tag/v3.1) (2016-09-18)

Includes bug fixes and other changes made in the commits since v3.0.

### Changed
*   no longer uses dynamic memory allocation


## 3.0 (November 2014)

Library re-design. Much more user friendly. No backwards compatibility.

Uploaded to GitHub to simplify any further development.

### Added
*   a display with any number of digits can be used
*   floats are supported
*   support for using transistors for switching


## [2.3](https://docs.google.com/file/d/0Bwrp4uluZCpNdE9oWTY0M3BncTA/edit?usp=sharing) (2013)
Allows for brightness control.


## 2.2
Allows 1, 2 or 3 digit displays to be used.


## 2.1
Includes a bug fix.


## 2.0
Now works for any digital pin arrangement.

Supports both common anode and common cathode displays.
