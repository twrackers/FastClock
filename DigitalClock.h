#ifndef _DIGITAL_CLOCK__H_
#define _DIGITAL_CLOCK__H_

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

#include "TimePiece.h"

class DigitalClock
{
  private:
    Adafruit_7segment m_display;
    TimePiece& m_timepiece;
    bool m_connected;
    
  public:
    DigitalClock(const byte i2c_addr, TimePiece& timepiece) :
    m_display(Adafruit_7segment()),
    m_timepiece(timepiece),
    m_connected(true)
    {
      m_display.begin(i2c_addr);
      Wire.beginTransmission(i2c_addr);
      byte rc = Wire.endTransmission();
      if (rc != 0) {
        m_connected = false;
      } else {
        showTime();
      }
    }

    void showTime()
    {
      if (m_connected) {
        const byte pos[] = { 0, 1, 3, 4 };
        const byte* digits = m_timepiece.getDigits();
        m_display.drawColon(true);
        for (byte i = 0; i < sizeof pos; ++i) {
          m_display.writeDigitNum(pos[i], digits[i]);
        }
        m_display.writeDisplay();
        }
    }

    bool isConnected() const
    {
      return m_connected;
    }
};


#endif

