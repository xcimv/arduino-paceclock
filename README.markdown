
# arduino-paceclock

This is a simple arduino paceclock that goes from 00:00 to 59:59.  It's only useful for testing electrical components because the arduino crystal has an accuracy of +/- a few seconds a day (less than two tenths of a second per hour); so, a real-time clock such as DS3231 should be used in paceclocks for training instead since it drifts less than a minute per year.

## Hardware

  * 1 x Arduino Uno
  * 4 x 7-segment common-anode LED array displays
  * 4 x 8-bit shift registers

## Pin setup

  * latch pin: 8
  * clock pin: 12
  * data pin: 11

## License

The project is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).
