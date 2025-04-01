#include "include/background.h"

BackgroundColor::Color24 BackgroundColor::lerp( const BackgroundColor::Color24 &A, const BackgroundColor::Color24 &B, float t ) const {
  return {
    (1 - t) * A.red + t * B.red,
    (1 - t) * A.green +t * B.green,
    (1 - t) * A.blue +t * B.blue,
  };
};

BackgroundColor::Color24 BackgroundColor::sampleUV(float u, float v) const {
  auto xt = lerp(BackgroundColor::corners[tl], corners[tr], u);
  auto xb =  lerp(BackgroundColor::corners[bl], corners[br], u);
  auto final = lerp(xt, xb, v);
  return final;
};

BackgroundColor::BackgroundColor(const std::vector<Color24> &colors) {
  for (auto i{0}; i < 4; ++i) {
    BackgroundColor::corners[i] = colors[i];
  }
}