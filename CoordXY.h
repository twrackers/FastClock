#ifndef _COORD_XY__H_
#define _COORD_XY__H_

struct Coord
{
  float x;
  float y;

  Coord() : x(0.0), y(0.0)
  {
  }

  Coord(const float xv, const float yv) :
  x(xv), y(yv)
  {
  }

  Coord& operator+=(const Coord& rhs)
  {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
  }

  Coord& operator-=(const Coord& rhs)
  {
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
  }

  friend Coord operator+(Coord lhs, const Coord& rhs)
  {
    lhs += rhs;
    return lhs;
  }

  friend Coord operator-(Coord lhs, const Coord& rhs)
  {
    lhs -= rhs;
    return lhs;
  }

  float mag() const
  {
    return sqrt(x * x + y * y);
  }
};

#endif

