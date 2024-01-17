#include <StateMachine.h>

// Supports one type of display at a time.
// Uncomment ONE of the following lines.
#include "SparkFun_Alphanumeric.h"
//#include "SparkFun_OLED.h"

#define FAST 12
#define INTERVAL (60000L / FAST)

StateMachine timer(INTERVAL, true);

Display display;

int hr = 0;
int mn = 0;

void setup() {

  display.begin();
  display.showTime(hr, mn);
  
}

void loop() {
  if (timer.update()) {
    if (++mn == 60) {
      mn = 0;
      if (++hr == 24) {
        hr = 0;
      }
    }
    display.showTime(hr, mn);
  }
}
