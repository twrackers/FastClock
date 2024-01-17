#include <StateMachine.h>

// Supports one type of display at a time.
// Uncomment ONE of the following lines.
#include "SparkFun_Alphanumeric.h"
//#include "SparkFun_OLED.h"

// Speedup factor over real time
#define FAST 12
#define INTERVAL (60000L / FAST)

// Update timer
StateMachine timer(INTERVAL, true);

// Display class, defined in each header file
Display display;

// Current fast time
int hr = 0;
int mn = 0;

void setup() {

  // Start up and initialize display.
  display.begin();
  display.showTime(hr, mn);
  
}

void loop() {

  // If time to update fast clock...
  if (timer.update()) {
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
    display.showTime(hr, mn);
  }
  
}
