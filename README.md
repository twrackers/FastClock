# FastClock-sketches

This is a collection of Arduino sketches which run as "fast clocks" used in model railroading.

## FastClock

This sketch produces a simple fast-clock display on one of several small displays.  Which one is used is selected by uncommenting one of several `#include` lines near the top of the `FastClock.ino` file.

| Header file | Display | Default Address |
| ----------- | ------- | --------------- |
| `Adafruit_LED.h` | Adafruit 7-Segment Backpack | 0x70 |
| `SparkFun_Alphanumeric.h` | SparkFun Qwiic Alphanumeric Display | 0x70 |
| `SparkFun_OLED.h` | SparkFun Qwiic - OLED - (1.3in., 128x64) | 0x3D |
