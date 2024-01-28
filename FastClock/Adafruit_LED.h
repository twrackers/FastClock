#ifndef _ADAFRUIT_LED__H_
#define _ADAFRUIT_LED__H_

#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

class Display {

  private:
    Adafruit_7segment m_disp;

  public:
    Display() {
    }
    
    bool begin() {

      if (!m_disp.begin(0x77)) {
        return false;
      }

      m_disp.clear();
      m_disp.setDisplayState(true);
      m_disp.drawColon(true);
      return true;
      
    }
    
    void showTime(const byte hr, const byte mn) {

      String str;
      str.reserve(4);
      str.concat(hr / 10);
      str.concat(hr % 10);
      str.concat(mn / 10);
      str.concat(mn % 10);
      
      m_disp.println(str);
      m_disp.writeDisplay();
      
    }
  
};

#endif
