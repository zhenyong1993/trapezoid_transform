#include "RRLogger.h"
#include "Quadrilateral.h"

bool find_max_inner_rect()
{
  RRLogger::GetInstance(false, "debug");

  Quadrilateral quad({0.0, 1.0}, {1.0, 0.0}, {2.0, 1.0}, {1.0, 2.0});
  auto vertices = quad.MaxInnerRect(4.0f / 3);
  for (auto p : vertices) {
    RRLOG_INFO("vertice: {}, {}", p.x, p.y);
  }
  return (4 == vertices.size());
}
