// FastClock_Stateful
//
// Fast clock code, runs on any Arduino-class microcontroller
// which allows serial output.  (There are a few which do not.)
//
// This sketch is similar to FastClock_NoDelay, except the timing code
// is handled by a StateMachine object, which allows the sketch
// to loop in "hard real-time".  See these other sketches for simpler
// examples of fast-clock codes.
//
// - FastClock_QnD: "quick and dirty" using delay()
// - FastClock_NoDelay: timing without using delay()

#include <Arduino.h>

// Arduino library to define "finite state machine" objects, which is
// downloadable from https://github.com/twrackers/StateMachine-library.
//
// Installation instructions can be found at
// https://github.com/twrackers/StateMachine-library/blob/main/INSTALL.md.

#include <StateMachine.h>

void showTime(const unsigned long when,
              const int hr, const int mn) {

  Serial.print(((float) when / 1000.0), 3);
  Serial.print(' ');
  Serial.print(hr / 10);
  Serial.print(hr % 10);
  Serial.print(':');
  Serial.print(mn / 10);
  Serial.println(mn % 10);

}

// Speedup factor over real time
// INTERVAL will be in milliseconds.
#define FAST 24
#define INTERVAL (60000L / FAST)

// StateMachine object to handle timing in real-time mode
StateMachine pacer(INTERVAL, true);

// Current fast time
int hr = 0;
int mn = 0;

void setup() {

  // Set up serial output.
  // "Serial Monitor" in Tools menu must be set to match.
  Serial.begin(115200);
  while (!Serial) {
    delay(1);
  }

  // Show the starting time.
  unsigned long now = millis();
  Serial.println("Starting at... ");
  showTime(now, hr, mn);
  
}

void loop() {
  
  // Time to update?
  if (pacer.update()) {
    
    unsigned long now = millis();

    // Increment minutes, and if necessary...
    if (++mn == 60) {
      // ... zero minutes...
      mn = 0;
      // ... and increment hours, and if necessary...
      if (++hr == 24) {
        // ... zero hours.
        hr = 0;
      }
    }
    
    // Display updated fast time.
    showTime(now, hr, mn);
  
  }
  
}
