#include "libs/core/two_vertices.h"

#include <cassert>
#include <cmath>
#include <numbers>
#include <string>

namespace core
{
  two_vertices::two_vertices(int v1, int v2)
    : v1(v1)
    , v2(v2)
  {}

  void two_vertices::insert(int v)
  {
    if(v1 == v || v2 == v)
      return;
    assert(this->size() < 2);
    (v1 == -1 ? v1 : v2) = v;
  }

  void two_vertices::erase(int v)
  {
    if(v1 == v)
    {
      v1 = -1;
    }
    else if(v2 == v)
    {
      v2 = -1;
    }
  }

  void two_vertices::replace(int u, int v)
  {
    if(v1 == u)
    {
      v1 = v;
    }
    else if(v2 == u)
    {
      v2 = v;
    }
    else
    {
      insert(v);
    }
  }

  int two_vertices::max() const
  {
    assert(v1 != -1 || v2 != -1);
    return std::max(v1, v2);
  }

  int two_vertices::min() const
  {
    if(v1 != -1 && v2 != -1)
    {
      return std::min(v1, v2);
    }
    assert(v1 != -1 || v2 != -1);
    return v1 != -1 ? v1 : v2;
  }

  int two_vertices::size() const
  {
    return (v1 != -1) + (v2 != -1);
  }
}  // namespace geo