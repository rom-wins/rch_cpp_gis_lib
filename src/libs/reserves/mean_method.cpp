#include "libs/core/functions.h"
#include "libs/reserves/triangles_method.h"
#include "libs/triangulation/triangulation.h"

#include <algorithm>
#include <iostream>
#include <set>

namespace reserves::mean_method
{
  void calc_reserves(std::vector<core::point> input_points)
  {
    const auto builder = triangulation::triangulation_builder::create(std::move(input_points));
    const auto& triangulation = builder->get();
    const auto triangles = triangulation::build_triangles(triangulation.graph);

    const auto& points = triangulation.points;

    double square = 0.0;
    for(const auto& triangle : triangles)
      square += core::calculate_square_2d(points.at(triangle.p1),
                                          points.at(triangle.p2),
                                          points.at(triangle.p3));

    double sum_thickness = 0.0;
    double sum_content = 0.0;
    double sum_density = 0.0;

    for(const auto& point : points)
    {
      sum_thickness += point.get_thickness();
      sum_content += point.get_content();
      sum_density += point.get_density();
    }

    double mean_thickness = sum_thickness / points.size();
    double mean_content = sum_content / points.size();
    double mean_density = sum_density / points.size();

    double volume = mean_thickness * square;
    double reserve = volume * mean_density;
    double reserve_useful_component = reserve * mean_content * 0.01;

    std::cout << "-------------------MEAN METHOD-------------------" << std::endl;
    std::cout << "     S = " << square << std::endl;
    std::cout << "     M = " << mean_thickness << std::endl;
    std::cout << "     C = " << mean_content << std::endl;
    std::cout << "     p = " << mean_density << std::endl;
    std::cout << "     V = " << volume << std::endl;
    std::cout << "     Q = " << reserve << std::endl;
    std::cout << "     P = " << reserve_useful_component << std::endl;
    std::cout << "-----------------END MEAN METHOD-----------------" << std::endl;
  }
}  // namespace reserves::mean_method