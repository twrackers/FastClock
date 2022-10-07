#ifndef _TIME_PIECE__H_
#define _TIME_PIECE__H_

#include <StateMachine.h>

class TimePiece : public StateMachine
{
  private:
    const byte m_scale;
    byte m_digits[4];
    byte m_hour;
    byte m_minute;
    byte m_tenth;
    bool m_running;
    bool m_tic;

    void x_decode()
    {
      m_digits[0] = m_hour / 10;
      m_digits[1] = m_hour % 10;
      m_digits[2] = m_minute / 10;
      m_digits[3] = m_minute % 10;
    }

  public:
    TimePiece(const byte scale, const byte hour) :
    StateMachine((12000U / scale), true),
    m_scale(scale),
    m_hour(hour), m_minute(0), m_tenth(0),
    m_running(false), m_tic(true)
    {
      x_decode();
    }

    virtual bool update()
    {
      if (StateMachine::update()) {
        if (m_running) {
          m_tenth += 2;
          if (m_tenth == 10) {
            m_tenth = 0;
            m_tic = true;
            if (++m_minute == 60) {
              m_minute = 0;
              if (++m_hour == 24) {
                m_hour = 0;
              }
            }
          } else {
            m_tic = false;
          }
          x_decode();
        }
        return true;
      }
      return false;
    }

    void run()
    {
      m_running = true;
    }

    void stop()
    {
      m_running = false;
    }

    bool tic() const
    {
      return m_tic;
    }

    void write(const byte hr, const byte mn)
    {
      m_hour = hr;
      m_minute = mn;
    }

    void read(byte& hr, byte& mn, byte& tenth) const
    {
      hr = m_hour;
      mn = m_minute;
      tenth = m_tenth;
    }

    float read() const
    {
      return (float) m_hour * 60.0 
             + (float) m_minute
             + (float) m_tenth * 0.1;
    }

    const byte* getDigits() const
    {
      return m_digits;
    }

    bool isRunning() const
    {
      return m_running;
    }

    const byte getScale() const
    {
      return m_scale;
    }
};

#endif

