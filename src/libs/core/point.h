#pragma once

#include <functional>
#include <string>
#include <unordered_set>

namespace core
{
  class point
  {
  public:
    point();
    point(double x, double y, double z);
    point(double x, double y);
    point(double x,
          double y,
          double z,
          double z_roof,
          double thickness,
          double content,
          double density);

    double get_x() const;
    double get_y() const;
    double get_z() const;
    double get_z_roof() const;
    double get_thickness() const;
    double get_content() const;
    double get_density() const;

    void set_z_roof(double z_roof);
    void set_z(double z);

    point operator+(const point& rhs) const;
    point operator-(const point& rhs) const;
    point operator-() const;

  private:
    double m_x{};
    double m_y{};
    double m_z{};
    double m_z_roof{};
    double m_thickness{};
    double m_content{};
    double m_density{};
  };

  struct point_hasher
  {
    std::size_t operator()(const point& point) const
    {
      return std::hash<double>()(point.get_x()) * 23 + std::hash<double>()(point.get_y());
    }
  };

  struct point_equal
  {
    bool operator()(const point& lhs, const point& rhs) const
    {
      return lhs.get_x() == rhs.get_x() && lhs.get_y() == rhs.get_y();
    }
  };

  using unordered_set_of_points =
    std::unordered_set<core::point, core::point_hasher, core::point_equal>;
}  // namespace core