#include "libs/reserves/triangles_method.h"

#include "libs/core/functions.h"
#include "libs/triangulation/triangulation.h"

#include <algorithm>
#include <iostream>
#include <set>

namespace
{
  double calculate_incidence_angle(const core::point& p1,
                                   const core::point& p2,
                                   const core::point& p3,
                                   std::function<double(const core::point&)> get_z)
  {
    double left_det_A = p2.get_y() * get_z(p3) + p1.get_y() * get_z(p2) + p3.get_y() * get_z(p1);
    double left_det_B = p1.get_x() * get_z(p3) + p3.get_x() * get_z(p2) + p2.get_x() * get_z(p1);
    double left_det_C = p1.get_x() * p2.get_y() + p3.get_x() * p1.get_y() + p2.get_x() * p3.get_y();

    double right_det_A = -get_z(p1) * p2.get_y() - p1.get_y() * get_z(p3) - p3.get_y() * get_z(p2);
    double right_det_B = -get_z(p1) * p3.get_x() - p2.get_x() * get_z(p3) - get_z(p2) * p1.get_x();
    double right_det_C =
      -p2.get_y() * p3.get_x() - p3.get_y() * p1.get_x() - p2.get_x() * p1.get_y();

    double det_A = left_det_A + right_det_A;
    double det_B = left_det_B + right_det_B;
    double det_C = left_det_C + right_det_C;

    auto C_2 = det_C * det_C;

    double length_N1 = sqrt(det_A * det_A + det_B * det_B + C_2);
    double length_N2 = sqrt(C_2);

    return acos(C_2 / (length_N1 * length_N2));
  }
}  // namespace

namespace reserves::triangles_method
{
  void calc_reserves(std::vector<core::point> points)
  {
    const auto builder = triangulation::triangulation_builder::create(std::move(points));
    const auto& triangulation = builder->get();

    const auto triangles = triangulation::build_triangles(triangulation.graph);

    auto sum_volume = 0.0;
    auto sum_reserve = 0.0;
    auto sum_reserve_useful_component = 0.0;

    for(const auto& triangle : triangles)
    {
      const auto& p1 = triangulation.points.at(triangle.p1);
      const auto& p2 = triangulation.points.at(triangle.p2);
      const auto& p3 = triangulation.points.at(triangle.p3);

      const auto roof_area =
        core::calculate_square_3d(p1, p2, p3, [](const core::point& p) { return p.get_z_roof(); });

      const auto sole_area = core::calculate_square_3d(
        p1,
        p2,
        p3,
        [](const core::point& p) { return p.get_z_roof() - p.get_thickness(); });

      auto mean_area = (roof_area + sole_area) / 2;

      auto incidence_angle =
        calculate_incidence_angle(p1, p2, p3, [](const core::point& p) { return p.get_z_roof(); });

      auto mean_true_thickness =
        (p1.get_thickness() + p2.get_thickness() + p3.get_thickness()) * cos(incidence_angle) / 3;
      auto mean_content = (p1.get_content() + p2.get_content() + p3.get_content()) / 3;
      auto mean_density = (p1.get_density() + p2.get_density() + p3.get_density()) / 3;

      auto volume = mean_area * mean_true_thickness;
      auto reserve = volume * mean_density;
      auto reserve_useful_component = reserve * mean_content * 0.01;

      sum_volume += volume;
      sum_reserve += reserve;
      sum_reserve_useful_component += reserve_useful_component;
    }

    std::cout << "-----------------TRIANGLE METHOD-----------------" << std::endl;
    std::cout << "     V = " << sum_volume << std::endl;
    std::cout << "     Q = " << sum_reserve << std::endl;
    std::cout << "     P = " << sum_reserve_useful_component << std::endl;
    std::cout << "---------------END TRIANGLE METHOD---------------" << std::endl;
  }
}  // namespace reserves::triangles_method