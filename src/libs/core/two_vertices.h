#pragma once

#include <functional>
#include <string>
#include <unordered_set>

namespace core
{
  struct two_vertices
  {
    two_vertices(int v1 = -1, int v2 = -1);
    void insert(int v);
    void erase(int v);
    void replace(int u, int v);
    int max() const;
    int min() const;
    int size() const;

    int v1;
    int v2;
  };
}  // namespace geo