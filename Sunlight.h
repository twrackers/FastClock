#ifndef _SUNLIGHT__H_
#define _SUNLIGHT__H_

#include <Streaming.h>
#include <math.h>

#include "ColorSpace.h"
#include "CoordXY.h"

const ColorRGB midnightBlue = ColorHSV(240.0, 1.0, 0.02).toRGB();
const ColorRGB skyBlue = ColorHSV(240.0, 0.4, 0.05).toRGB();

// midnight is 0 degrees, noon is 180 degrees, etc.
float SunAngle(const byte hr, const byte mn)
{
  uint16_t tm = (uint16_t) hr * 60 + (uint16_t) mn;
  return (float) tm / 4.0;
}

// minutes = 0.0 at midnight, 720.0 at noon
float SunAngle(float minutes)
{
  return minutes / 4.0;
}

bool isClose(const float a, const float b, const float eps = 1.0e-3)
{
  return fabs(a - b) < eps;
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float calcHeight(const Coord& obs, const float path, const float theta)
{
  // Point w/r/t observer.
  Coord p(path * sin(theta), path * cos(theta));
  // Change to w/r/t earth center.
  p += obs;
  // Calculate height above surface.
  return p.mag() - obs.mag();
}

float lightPath(const float sunAngle)
{
  // Origin is earth center.
  // sunAngle =
  //    0: nadir
  //   90: east horizon
  //  180: zenith
  //  270: west horizon
  
  const float dAtmos = 5.0;             // miles
  const float rEarth = 4000;            // miles
  const float rAtmos = rEarth + dAtmos; // miles
  const Coord obs(0.0, rEarth);         // observer position

  // theta is angle from zenith, in radians.
  float theta = radians(180.0 - sunAngle);
  // Bracket light path length.
  float minPath = dAtmos;
  float maxPath = 50.0 * minPath;
  float path;   // working value
  while (true) {
    // Binary search for desired path length.
    path = (minPath + maxPath) / 2.0;
    // Calculate height above surface where this path ends.
    float h = calcHeight(obs, path, theta);
    // Done when we're close enough to desired height.
    if (isClose(h, dAtmos)) break;
    // Otherwise, adjust bracket.
    if (h < dAtmos) {
      minPath = path;
    } else {
      maxPath = path;
    }
  }
  return path;
}

ColorRGB indirectLight(const float sunAngle, const float viewAngle, const float path)
{
  const float twilightAngle = 15.0;
    
  if (sunAngle < (90.0 - twilightAngle)  ||  sunAngle > (270.0 + twilightAngle)) {
    // night
    return midnightBlue;
  } else if (sunAngle > 90.0  &&  sunAngle < 270.0) {
    // day
    return skyBlue;
  } else {
    if (sunAngle < 180.0) {
      // dawn
      float beginAngle = (viewAngle - 90.0) / 180.0 * 15.0 + 90.0 - twilightAngle;
      float endAngle = 90.0;
      float f = constrain((sunAngle - beginAngle) / (endAngle - beginAngle), 0.0, 1.0);
      return (1.0 - f) * midnightBlue + f * skyBlue;
    } else {
      // dusk
      float beginAngle = 270.0;
      float endAngle = (viewAngle - 270.0) / 180.0 * 15.0 + 270.0 + twilightAngle;
      float f = constrain((sunAngle - beginAngle) / (endAngle - beginAngle), 0.0, 1.0);
      return (1.0 - f) * skyBlue + f * midnightBlue;
    }
  }
}

ColorRGB directLight(const float sunAngle, const float viewAngle, const float path)
{
  const float width = 15.0;

  if (sunAngle < 60.0  ||  sunAngle > 300.0) {
    return ColorRGB(0.0, 0.0, 0.0);
  } else {
    float angle = sunAngle - viewAngle;
    float ex = (angle * angle) / (2.0 * width * width);
    float value = 2.0 / (exp(-ex) + exp(ex)) * exp(-path / 500.0);
    float hue = fmap(path, 10.0, 250.0, 60.0, 15.0);
    float saturation = fmap(path, 10.0, 250.0, 0.75, 1.0);
//    Serial << path << ' ' << hue << ' ' << saturation << ' ' << value << endl;
    return ColorHSV(hue, saturation, value).toRGB();
  }
}

ColorRGB skyColor(const float sunAngle, const float viewAngle)
{
  bool twilight = (sunAngle < 90.0)  ||  (sunAngle > 270.0);
  float path = twilight ? 250.0 : lightPath(sunAngle);
  return maxOf(
    indirectLight(sunAngle, viewAngle, path),
    directLight(sunAngle, viewAngle, path)
  );
}

#endif

