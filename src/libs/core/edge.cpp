#include "libs/core/edge.h"

#include <cmath>
#include <numbers>
#include <string>

namespace core
{
  edge::edge(int _v1, int _v2)
    : v1(_v1)
    , v2(_v2)
  {}

  bool edge::operator==(const edge& other) const
  {
    return v1 == other.v1 && v2 == other.v2;
  }
}  // namespace geo