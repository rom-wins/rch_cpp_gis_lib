#include "libs/core/point.h"

#include <cmath>
#include <numbers>
#include <string>

namespace core
{
  point::point() = default;
  point::point(double x, double y, double z)
    : m_x(x)
    , m_y(y)
    , m_z(z)
  {}

  point::point(double x,
               double y,
               double z,
               double z_roof,
               double thickness,
               double content,
               double density)
    : m_x(x)
    , m_y(y)
    , m_z(z)
    , m_z_roof(z_roof)
    , m_thickness(thickness)
    , m_content(content)
    , m_density(density)
  {}

  point::point(double x, double y)
    : m_x(x)
    , m_y(y)
  {}


  double point::get_x() const
  {
    return m_x;
  }

  double point::get_y() const
  {
    return m_y;
  }

  double point::get_z() const
  {
    return m_z;
  }

  double point::get_z_roof() const
  {
    return m_z_roof;
  }

  double point::get_thickness() const
  {
    return m_thickness;
  }

  double point::get_content() const
  {
    return m_content;
  }

  double point::get_density() const
  {
    return m_density;
  }

  point point::operator+(const point& other) const
  {
    return {m_x + other.m_x,
            m_y + other.m_y,
            m_z + other.m_z,
            m_z_roof + other.m_z_roof,
            m_thickness + other.m_thickness,
            m_content + other.m_content,
            m_density + other.m_density};
  }

  point point::operator-(const point& other) const
  {
    return {m_x - other.m_x,
            m_y - other.m_y,
            m_z - other.m_z,
            m_z_roof - other.m_z_roof,
            m_thickness - other.m_thickness,
            m_content - other.m_content,
            m_density - other.m_density};
  }

  point point::operator-() const
  {
    return {-m_x, -m_y, -m_z, -m_z_roof, -m_thickness, -m_content, -m_density};
  }
}  // namespace core