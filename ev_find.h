#pragma once
#include <cstdint>
#include <vector>

// Raw-timing frames that mimic the 4-button item-finder remote (id 3C690).
//
// Measured on 2026-11-09 with an SX1262 envelope recorder next to the real remote
// (ESPHome's rc_switch protocol 1 was NOT close enough for the fobs to react):
//   T ~= 395 us
//   24 data bits, 4T each:  0 = H T + L 3T,   1 = H 3T + L T
//   then 3x (H T + L T)
//   then   H T + L ~10T     (sync gap, ~4 ms)
//   frame period ~44.6 ms; a real key press is only ~4-5 frames.
// Positive values = carrier on (us), negative = carrier off.
inline std::vector<int32_t> finder_frame(uint32_t code24, int repeats) {
  const int32_t T = 395;
  std::vector<int32_t> v;
  v.reserve(static_cast<size_t>(repeats) * 56);
  for (int r = 0; r < repeats; r++) {
    for (int i = 23; i >= 0; i--) {
      if ((code24 >> i) & 1) {
        v.push_back(3 * T);
        v.push_back(-T);
      } else {
        v.push_back(T);
        v.push_back(-3 * T);
      }
    }
    for (int k = 0; k < 3; k++) {
      v.push_back(T);
      v.push_back(-T);
    }
    v.push_back(T);
    v.push_back(-10 * T);
  }
  return v;
}
