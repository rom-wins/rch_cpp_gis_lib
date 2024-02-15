#pragma once

#include "libs/core/point.h"

#include <functional>

namespace core
{
  double cross_product(const point& lhs, const point& rhs);

  double calculate_square_3d(const point& point_1,
                             const point& point_2,
                             const point& point_3,
                             std::function<double(const point&)> get_z);
  double calculate_square_2d(const point& point_1, const point& point_2, const point& point_3);

  double calculate_length_3d(const point& point_1,
                             const point& point_2,
                             std::function<double(const point&)> get_z);
  double calculate_length_2d(const point& point_1, const point& point_2);

  double inverse_geodesic_task(const point& point_1, const point& point_2);
}  // namespace core
