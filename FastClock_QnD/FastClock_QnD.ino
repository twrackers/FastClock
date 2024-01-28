// FastClock_QnD
//
// Fast clock code, runs on any Arduino-class microcontroller
// which allows serial output.  (There are a few which do not.)
//
// This sketch is a "quick and dirty" version of a fast-clock code,
// which uses the delay(...) function to set the update rate of the
// clock.  Note that this code will run a little slow because it
// does not compensate for the small amount of processor time used
// by the code in loop() other than the delay(...) call.  See these
// sketches for examples of more accurate fast-clock codes.
//
// - FastClock_NoDelay: more accurate timing without using delay()
// - FastClock_Stateful: timing using a StateMachine object

#include <Arduino.h>

// Speedup factor over real time
// INTERVAL will be in milliseconds.
#define FAST 24
#define INTERVAL (60000L / FAST)

// Current fast time
int hr = 0;
int mn = 0;

void showTime(const unsigned long when,
              const int hr, const int mn) {

  Serial.print(when);
  Serial.print(' ');
  Serial.print(hr / 10);
  Serial.print(hr % 10);
  Serial.print(':');
  Serial.print(mn / 10);
  Serial.println(mn % 10);

}

void setup() {

  // Set up serial output.
  // "Serial Monitor" in Tools menu must be set to match.
  Serial.begin(115200);
  while (!Serial) {
    delay(1);
  }

  // Show the starting time, and set the time for the first update.
  unsigned long now = millis();
  showTime(now, hr, mn);
  
}

void loop() {

  delay(INTERVAL);

  unsigned long now = millis();
  
  // Increment minutes, and if necessary...
  if (++mn == 60) {
    // ... zero minutes...
    mn = 0;
    // ... and increment hours, and if necessary...
    if (++hr == 24) {
      // ... zero hours too.
      hr = 0;
    }
  }
  
  // Display updated fast time.
  showTime(now, hr, mn);

}
