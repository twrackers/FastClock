#ifndef _SUNLIGHT__H_
#define _SUNLIGHT__H_

#include <math.h>

#include <Qwiic_LED_Stick.h>
#define NUM_LEDS 10

static void decode(const uint32_t rgb, byte& r, byte& g, byte& b) {
  r = (rgb >> 16) & 0xFF;
  g = (rgb >> 8) & 0xFF;
  b = rgb & 0xFF;
}

class Sunlight {

  private:
    LED m_stick;
    byte m_sky_red[NUM_LEDS];
    byte m_sky_grn[NUM_LEDS];
    byte m_sky_blu[NUM_LEDS];

  public:
    Sunlight() {
    }
    
    bool begin() {
      if (!m_stick.begin()) {
        return false;
      }
      for (byte i = 0; i < NUM_LEDS; ++i) {
        m_sky_red[i] = m_sky_grn[i] = 0x00;
        m_sky_blu[i] = 0x01;
        m_stick.setLEDColor(i, m_sky_red[i], m_sky_grn[i], m_sky_blu[i]);
      }
      return true;
    }

    void illuminate(const byte hr, const byte mn) {
      if (hr >= 6 && hr < 18) {
        int daylight = (hr - 12) * 60 + mn;
        float elev = (float) (daylight / 6) * HALF_PI;
        float illum = cos(elev);
      }
    }
};

#endif
