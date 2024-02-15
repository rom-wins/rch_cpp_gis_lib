#pragma once

#include <functional>
#include <string>
#include <unordered_set>

namespace core
{
  struct edge
  {
    edge(int _v1 = -1, int _v2 = -1);
    bool operator==(const edge& other) const;

    int v1;
    int v2;
  };

  struct edge_hash
  {
    std::hash<int> int_hash;
    std::size_t operator()(const edge& edge) const
    {
      std::size_t lhs = int_hash(edge.v1);
      std::size_t rhs = int_hash(edge.v2);
      lhs ^= rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2);
      return lhs;
    }
  };
}  // namespace geo