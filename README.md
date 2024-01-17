# FastClock-sketches

This is a collection of Arduino sketches which run as "fast clocks" used in model railroading.

## FastClock

This sketch produces a simple fast-clock display on one of several small displays.  Which one is used is selected by uncommenting one of several `#include` lines near the top of the `FastClock.ino` file.

| Header file | Display |
| ----------- | ------- |
| `SparkFun_Alphanumeric.h` | SparkFun Qwiic Alphanumeric Display |
| `SparkFun_OLED.h` | SparkFun Qwiic - OLED - (1.3in., 128x64) |
