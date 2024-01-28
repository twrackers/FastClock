// FastClock_NoDelay
//
// Fast clock code, runs on any Arduino-class microcontroller
// which allows serial output.  (There are a few which do not.)
//
// This sketch is similar to FastClock_QnD, except the timing does NOT
// use the delay(...) function.  This eliminates timing drift caused
// by the small amount of time used on each pass through loop()
// outside of the delay call.  See these other sketches for other
// examples of fast-clock codes.
//
// - FastClock_QnD: "quick and dirty" using delay()
// - FastClock_Stateful: timing using a StateMachine object

#include <Arduino.h>

// Speedup factor over real time
// INTERVAL will be in milliseconds.
#define FAST 24
#define INTERVAL (60000L / FAST)

// Clock time for next update (milliseconds)
unsigned long update_at;

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
  update_at = now + INTERVAL;
  
}

void loop() {
  
  // Time to update?
  unsigned long now = millis();
  if ((long) (now - update_at) >= 0L) {

    // Set up time for next update.
    update_at = now + INTERVAL;
    
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
  
}
