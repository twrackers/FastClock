#ifndef _SPARKFUN_OLED__H_
#define _SPARKFUN_OLED__H_

#include <SparkFun_Qwiic_OLED.h>
#include <res/qw_fnt_largenum.h>

class Display {

  private:
    Qwiic1in3OLED m_disp;
    uint16_t m_width;
    uint16_t m_height;

  public:
    Display() {
    }
    
    bool begin() {
    
      if (!m_disp.begin()) {
        return false;
      }

      m_disp.setFont(QW_FONT_LARGENUM);
      m_disp.erase();
      m_disp.display();

      m_width = m_disp.getWidth();
      m_height = m_disp.getHeight();

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
      
      uint16_t x = (m_width - m_disp.getStringWidth(str)) / 2;
      uint16_t y = (m_height - m_disp.getStringHeight(str)) / 2;
      
      m_disp.erase();
      m_disp.text(x, y, str);
      m_disp.display();
      
    }
  
};

#endif
