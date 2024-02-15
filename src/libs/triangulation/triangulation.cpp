#include "libs/core/functions.h"
#include "libs/triangulation/triangulation.h"

#include <algorithm>

namespace triangulation
{
  namespace
  {
    triangle get_triangle(int p1, int p2, int p3)
    {
      std::vector<int> first_triangle{p1, p2, p3};
      std::sort(first_triangle.begin(), first_triangle.end());
      return {first_triangle.at(0), first_triangle.at(1), first_triangle.at(2)};
    }

    const auto eps = 1e-9;
  }  // namespace

  triangulation_builder::triangulation_builder(std::vector<core::point> points) noexcept
  {
    m_triangulation.points = std::move(points);
  }

  const delauney_triangulation& triangulation_builder::get() const
  {
    return m_triangulation;
  }

  std::unique_ptr<triangulation_builder> triangulation_builder::create(
    std::vector<core::point> points)
  {
    triangulation_builder builder(std::move(points));
    builder.build();
    return std::make_unique<triangulation_builder>(std::move(builder));
  }

  bool triangulation_builder::check_delaunay_condition(int left,
                                                       int right,
                                                       int outer,
                                                       int inner) const
  {
    const auto& l = m_triangulation.points[left];
    const auto& r = m_triangulation.points[right];
    const auto& t /*top*/ = m_triangulation.points[outer];
    const auto& b /*bottom*/ = m_triangulation.points[inner];

    if(outer == inner)
      return true;

    if(cross_product(l - t, b - t) < 0 || cross_product(r - t, b - t) > 0)
      return true;

    const auto Sa = (t.get_x() - r.get_x()) * (t.get_x() - l.get_x()) +
                    (t.get_y() - r.get_y()) * (t.get_y() - l.get_y());
    const auto Sb = (b.get_x() - r.get_x()) * (b.get_x() - l.get_x()) +
                    (b.get_y() - r.get_y()) * (b.get_y() - l.get_y());

    if(Sa > -eps && Sb > -eps)
      return true;

    if(!(Sa < 0 && Sb < 0))
    {
      auto Sc = cross_product(t - r, t - l);
      auto Sd = cross_product(b - r, b - l);

      if(Sc < 0)
        Sc = -Sc;

      if(Sd < 0)
        Sd = -Sd;

      if(Sc * Sb + Sa * Sd > -eps)
        return true;
    }

    return false;
  }

  void triangulation_builder::fix_triangulation(int left, int right, int outer)
  {
    auto& graph = m_triangulation.graph;

    m_recursion_stack[0] = core::edge{left, right};
    int stack_size = 1;

    while(stack_size > 0)
    {
      left = m_recursion_stack[stack_size - 1].v1;
      right = m_recursion_stack[stack_size - 1].v2;
      --stack_size;

      int inner = graph[core::edge{std::min(left, right), std::max(left, right)}].min();

      if(check_delaunay_condition(left, right, outer, inner))
      {
        graph[core::edge{right, outer}].insert(left);
        graph[core::edge{left, outer}].insert(right);
        if(right < left)
          std::swap(right, left);

        graph[core::edge{left, right}].insert(outer);
        continue;
      }

      graph[core::edge{right, outer}].replace(left, inner);
      graph[core::edge{left, outer}].replace(right, inner);
      graph[core::edge{std::min(inner, left), std::max(inner, left)}].replace(right, outer);
      graph[core::edge{std::min(inner, right), std::max(inner, right)}].replace(left, outer);

      graph.erase(core::edge{std::min(left, right), std::max(left, right)});

      m_recursion_stack[stack_size++] = core::edge{left, inner};
      m_recursion_stack[stack_size++] = core::edge{inner, right};
    }
  }

  void triangulation_builder::add_point_to_triangulation(int i)
  {
    auto& points = m_triangulation.points;

    int hull_pt = i - 1;
    auto last_vector = points[hull_pt] - points[i];
    int next_hull_pt = m_convex_hull[hull_pt].right;
    auto new_vector = points[next_hull_pt] - points[i];

    while(core::cross_product(last_vector, new_vector) > -eps)
    {
      fix_triangulation(hull_pt, next_hull_pt, i);

      hull_pt = next_hull_pt;
      last_vector = new_vector;
      next_hull_pt = m_convex_hull[hull_pt].right;
      new_vector = points[next_hull_pt] - points[i];
    }

    m_convex_hull[i].right = hull_pt;

    hull_pt = i - 1;
    last_vector = points[hull_pt] - points[i];
    next_hull_pt = m_convex_hull[hull_pt].left;
    new_vector = points[next_hull_pt] - points[i];

    while(core::cross_product(last_vector, new_vector) < eps)
    {
      fix_triangulation(next_hull_pt, hull_pt, i);

      hull_pt = next_hull_pt;
      last_vector = new_vector;
      next_hull_pt = m_convex_hull[hull_pt].left;
      new_vector = points[next_hull_pt] - points[i];
    }

    m_convex_hull[i].left = hull_pt;

    m_convex_hull[m_convex_hull[i].right].left = i;
    m_convex_hull[hull_pt].right = i;
  }

  void triangulation_builder::build()
  {
    auto& graph = m_triangulation.graph;
    auto& points = m_triangulation.points;

    // Размер стека рекурсии и МВО никогда не превышают количества точек
    m_recursion_stack.resize(points.size());
    m_convex_hull.resize(points.size());

    std::sort(points.begin(),
              points.end(),
              [](auto& lhs, auto& rhs) { return lhs.get_x() < rhs.get_x(); });

    if(points.size() < 3)
      return;

    m_convex_hull[0] = list_node{1, 1};
    m_convex_hull[1] = list_node{0, 0};
    graph[core::edge{0, 1}].insert(2);

    for(int i = 2; i < points.size(); ++i)
      add_point_to_triangulation(i);
  }

  std::vector<core::edge> build_convex_hull(const triangulation& triangulation)
  {
    std::vector<core::edge> convex_hull;
    for(const auto& [edge, two_vertices] : triangulation)
    {
      if(two_vertices.size() != 2)
        convex_hull.push_back(edge);
    }
    return convex_hull;
  }

  triangles build_triangles(const triangulation& triangulation)
  {
    triangles triangles;

    for(const auto& [edge, two_vertices] : triangulation)
    {
      if(two_vertices.v1 != -1)
        triangles.insert(get_triangle(edge.v1, edge.v2, two_vertices.v1));

      if(two_vertices.v2 != -1)
        triangles.insert(get_triangle(edge.v1, edge.v2, two_vertices.v2));
    }

    return triangles;
  }

  std::vector<core::edge> build_edges(const triangulation& triangulation)
  {
    std::vector<core::edge> edges;

    for(const auto& [edge, _] : triangulation)
      edges.push_back(edge);

    return edges;
  }
}  // namespace triangulation