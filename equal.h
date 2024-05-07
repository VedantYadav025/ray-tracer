#include <cmath>
const float Epsilon = 0.00001;

bool isEqual(const float& a, const float& b) {
  if (abs(a - b) < Epsilon) return true;
  return false;
}