# FastClock-sketches

This is a collection of Arduino sketches which run as "fast clocks" used in model railroading.

## FastClock_QnD

This sketch is a minimal "quick and dirty" fast-clock code which uses the `delay()` function for timing and the Arduino IDE's Serial Monitor for output.  Note that the use of the `delay()` function causes the timing of the main `loop()` function to lag a bit because the runtime of the non-delay portion is unknown.

## FastClock_NoDelay

This sketch improves the "quick and dirty" version by eliminating the call to the `delay()` function and using a call to `millis()` instead.  This is equivalent to the difference between the IDE example sketches `Blink` and `BlinkWithoutDelay`.  This change makes the timing as accurate as the Arduino's millisecond-clock.  The clock output is still written to the Serial Monitor.

## FastClock_Stateful

This sketch replaces timing code in the `.ino` file with calls to a [`StateMachine`](https://github.com/twrackers/StateMachine-library) object to encapsuate the timing logic.  Again, the clock output is written to the Serial Monitor.

## FastClock

This sketch replaces output to serial with one of several small external displays.  Which one is used is selected by uncommenting one of several `#include` lines near the top of the `FastClock.ino` file.  At this time, each of the supported displays would be connected to the microcontroller with a Qwiic I<sup>2</sup>C interface.  The [Adafruit Metro Mini](https://www.adafruit.com/product/2590) is one such processor board.

| Header file | Display | Default address | Used address |
| ----------- | ------- | ------- | ------- |
| [`Adafruit_LED.h`](https://www.adafruit.com/product/1269) | Adafruit 7-Segment Backpack | 0x70 | 0x77 |
| [`SparkFun_Alphanumeric.h`](https://www.sparkfun.com/products/16917) | SparkFun Qwiic Alphanumeric Display | 0x70 | 0x70 |
| [`SparkFun_OLED.h`](https://www.sparkfun.com/products/23453) | SparkFun Qwiic - OLED - (1.3in., 128x64) | 0x3D | 0x3D |

## FastClock_Stick

This sketch adds output to a [SparkFun Qwiic LED Stick](https://www.sparkfun.com/products/18354) to simulate adding an external bank of RGB lights which would be arranged over a model railroad to simulate movement of sunlight across the sky, casting changing shadows as the fast clock advances through daylight hours.