#ifndef _COLOR_SPACE__H_
#define _COLOR_SPACE__H_

#include <math.h>

struct ColorRGB
{
  float r;  // [0,1]
  float g;  // [0,1]
  float b;  // [0,1]

  ColorRGB(float red, float green, float blue) :
  r(red), g(green), b(blue)
  {
  }

  ColorRGB() : r(0.0), g(0.0), b(0.0)
  {
  }

  ColorRGB& operator+=(const ColorRGB& rhs)
  {
    this->r = min(1.0, this->r + rhs.r);
    this->g = min(1.0, this->g + rhs.g);
    this->b = min(1.0, this->b + rhs.b);
    return *this;
  }

  ColorRGB& operator*=(const float rhs)
  {
    this->r = min(1.0, this->r * rhs);
    this->g = min(1.0, this->g * rhs);
    this->b = min(1.0, this->b * rhs);
  }

  friend ColorRGB operator+(ColorRGB lhs, const ColorRGB& rhs)
  {
    lhs += rhs;
    return lhs;
  }

  friend ColorRGB operator*(ColorRGB lhs, const float rhs)
  {
    lhs *= rhs;
    return lhs;
  }

  friend ColorRGB operator*(const float lhs, const ColorRGB& rhs)
  {
    return rhs * lhs;
  }
};

ColorRGB maxOf(const ColorRGB& lhs, const ColorRGB& rhs)
{
  ColorRGB c;
  c.r = max(lhs.r, rhs.r);
  c.g = max(lhs.g, rhs.g);
  c.b = max(lhs.b, rhs.b);
  return c;
}

struct ColorHSV
{
  float h;  // [0,360)
  float s;  // [0,1]
  float v;  // [0,1]

  ColorHSV(float hu, float sa, float va) : h(hu), s(sa), v(va)
  {
  }

  ColorHSV() : h(0.0), s(0.0), v(0.0)
  {
  }

  ColorHSV& rotateHue(const float angle)
  {
    this->h += angle;
    if (this->h >= 360.0) {
      this->h -= 360.0;
    } else if (this->h < 0.0) {
      this->h += 360.0;
    }
    return *this;
  }

  ColorRGB toRGB() const
  {
    float c = s * v;
    float m = v - c;
    float x = c * (1.0 - fabs(fmod((h / 60.0), 2.0) - 1.0));
    float cm = c + m;
    float xm = x + m;
    byte sel = (byte) (h / 60.0);
    if (sel == 0) {
      return ColorRGB(cm, xm, m);
    } else if (sel == 1) {
      return ColorRGB(xm, cm, m);
    } else if (sel == 2) {
      return ColorRGB(m, cm, xm);
    } else if (sel == 3) {
      return ColorRGB(m, xm, cm);
    } else if (sel == 4) {
      return ColorRGB(xm, m, cm);
    } else if (sel == 5) {
      return ColorRGB(cm, m, xm);
    } else {
      return ColorRGB(m, m, m);
    }
  }
};

#endif

