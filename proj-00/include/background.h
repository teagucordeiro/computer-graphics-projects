#ifndef BACKGROUND
#define BACKGROUND
#include "vector"
#include "array"
#include <cstdint>

class BackgroundColor
{
using byte = std::uint8_t;

public:
  struct Color24
  {
    byte red;
    byte green;
    byte blue;
  };
  /// Ctro receives a list of four colors, for each corner.
  BackgroundColor(const std::vector<Color24> &colors);
  /// Dtro
  ~BackgroundColor() {};
  /// Sample and returns a color, based on the raster coordinate.
  Color24 sampleUV(float u, float v) const;

private:
  /// Corner indices.
  enum Corners_e
  {
    bl = 0, //!< Bottom left corner.
    tl,     //!< Top left corner.
    tr,     //!< Top right corner.
    br      //!< Bottom right corner.
  };

  /// Each corner has a color associated with.
  std::array<Color24, 4> corners{Color24{0, 0, 0}, Color24{0, 0, 0}, Color24{0, 0, 0}, Color24{0, 0, 0}};

  /// Return the linearly interpolated color in [A;B], based on the parameter \f$0\leq t \leq 1.\f$
  Color24 lerp(const Color24 &A, const Color24 &B, float t) const;
};
#endif