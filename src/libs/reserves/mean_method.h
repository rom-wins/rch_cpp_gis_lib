#pragma once
#include "libs/core/point.h"

#include <vector>

namespace reserves::mean_method
{
  void calc_reserves(std::vector<core::point> points);
}  // namespace reserves::mean_method