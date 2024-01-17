#ifndef _SPARKFUN_ALPHANUMERIC__H_
#define _SPARKFUN_ALPHANUMERIC__H_

#include <Wire.h>

#include <SparkFun_Alphanumeric_Display.h>

class Display {

  private:
    HT16K33 m_disp;
    
  public:
    Display() {
    }
    
    bool begin() {

      Wire.begin();
      
      if (!m_disp.begin()) {
        return false;
      }
      m_disp.displayOn();
      return true;
      
    }
    
    void showTime(const byte hr, const byte mn) {

      String str;
      str.reserve(5);
      str.concat(hr / 10);
      str.concat(hr % 10);
      str.concat(':');
      str.concat(mn / 10);
      str.concat(mn % 10);

      m_disp.print(str);
      m_disp.updateDisplay();
      
    }
  
};

#endif
