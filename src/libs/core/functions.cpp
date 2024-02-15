#include "libs/core/functions.h"
#include "libs/core/point.h"

#include <cmath>
#include <numbers>

namespace core
{
  double cross_product(const point& lhs, const point& rhs)
  {
    return lhs.get_x() * rhs.get_y() - lhs.get_y() * rhs.get_x();
  }

  double calculate_length_2d(const point& point_1, const point& point_2)
  {
    double dx = point_1.get_x() - point_2.get_x();
    double dy = point_1.get_y() - point_2.get_y();

    return std::sqrt(dx * dx + dy * dy);
  }

  double calculate_length_3d(const point& point_1,
                             const point& point_2,
                             std::function<double(const point&)> get_z)
  {
    double dx = point_1.get_x() - point_2.get_x();
    double dy = point_1.get_y() - point_2.get_y();
    double dz = get_z(point_1) - get_z(point_2);

    return std::sqrt(dx * dx + dy * dy + dz * dz);
  }

  double calculate_square_2d(const point& point_1, const point& point_2, const point& point_3)
  {
    auto a = calculate_length_2d(point_1, point_2);
    auto b = calculate_length_2d(point_2, point_3);
    auto c = calculate_length_2d(point_1, point_3);

    auto p = (a + b + c) / 2;

    return sqrt(p * (p - a) * (p - b) * (p - c));
  }

  double calculate_square_3d(const point& point_1,
                             const point& point_2,
                             const point& point_3,
                             std::function<double(const point&)> get_z)
  {
    auto a = calculate_length_3d(point_1, point_2, get_z);
    auto b = calculate_length_3d(point_2, point_3, get_z);
    auto c = calculate_length_3d(point_1, point_3, get_z);

    auto p = (a + b + c) / 2;

    return sqrt(p * (p - a) * (p - b) * (p - c));
  }

  double inverse_geodesic_task(const point& point_1, const point& point_2)
  {
    double dx = point_1.get_x() - point_2.get_x();
    double dy = point_1.get_y() - point_2.get_y();

    double az = std::atan2(dy, dx) * 180 / std::numbers::pi;
    if(az < 0)
      return 360 + az;

    return az;
  }
}  // namespace core
