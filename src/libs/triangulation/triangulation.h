#pragma once

#include "libs/core/edge.h"
#include "libs/core/point.h"
#include "libs/core/two_vertices.h"

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace triangulation
{
  struct list_node
  {
    int left;
    int right;
  };

  using triangulation = std::unordered_map<core::edge, core::two_vertices, core::edge_hash>;
  using list = std::vector<list_node>;

  struct delauney_triangulation
  {
    triangulation graph{};
    std::vector<core::point> points{};
  };

  class triangulation_builder
  {
  public:
    triangulation_builder(const triangulation_builder&) = delete;
    const triangulation_builder& operator=(const triangulation_builder&) = delete;
    triangulation_builder(triangulation_builder&&) = default;
    triangulation_builder& operator=(triangulation_builder&&) = default;

    const delauney_triangulation& get() const;

    static std::unique_ptr<triangulation_builder> create(std::vector<core::point> points);

  private:
    triangulation_builder(std::vector<core::point> points) noexcept;

    void build();

    void add_point_to_triangulation(int i /*index*/);

    void fix_triangulation(int left, int right, int outer);

    bool check_delaunay_condition(int left, int right, int outer, int inner) const;

    std::vector<core::edge> m_recursion_stack{};
    delauney_triangulation m_triangulation{};
    list m_convex_hull{};
  };

  struct triangle
  {
    int p1, p2, p3;
  };

  struct triangle_hash
  {
    std::size_t operator()(const triangle& triangle) const
    {
      return std::hash<int>()(triangle.p1) * 23 * 23 + std::hash<int>()(triangle.p2) * 23 +
             std::hash<int>()(triangle.p3);
    }
  };

  struct triangle_equal
  {
    bool operator()(const triangle& lhs, const triangle& rhs) const
    {
      return lhs.p1 == rhs.p1 && lhs.p2 == rhs.p2 && lhs.p3 == rhs.p3;
    }
  };

  using triangles = std::unordered_set<triangle, triangle_hash, triangle_equal>;

  std::vector<core::edge> build_convex_hull(const triangulation& triangulation);
  triangles build_triangles(const triangulation& triangulation);
  std::vector<core::edge> build_edges(const triangulation& triangulation);
}  // namespace triangulation