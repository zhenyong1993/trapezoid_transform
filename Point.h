#pragma once

#include "Constants.h"
#include <cfloat>
#include <cmath>
#include <sstream>
#include <string>

class Point2d {
public:
  Point2d(): x(0.0), y(0.0) {}

  Point2d(double x, double y)
  {
    this->x = x;
    this->y = y;
  }

  void Set(double x, double y)
  {
    this->x = x;
    this->y = y;
  }

  bool Equals(double x, double y) const
  {
    return ((fabs(this->x - x) <= EPSILON) && (fabs(this->y - y) <= EPSILON));
  }

  bool Equals(const Point2d& p) const
  {
    return Equals(p.x, p.y);
  }

  bool operator==(const Point2d& p) const
  {
    return Equals(p);
  }

  bool operator!=(const Point2d& p) const
  {
    return !(*this == p);
  }

  double Distance(const Point2d& p) const
  {
    return sqrt((this->x - p.x) * (this->x - p.x) + (this->y - p.y) * (this->y - p.y));
  }

  // 向量相加
  Point2d operator+(const Point2d& v) const
  {
    return Point2d(x + v.x, y + v.y);
  }

  // 向量相减
  Point2d operator-(const Point2d& v) const
  {
    return Point2d(x - v.x, y - v.y);
  }

  // 向量数乘
  Point2d Scalar(double c) const
  {
    return Point2d(c * x, c * y);
  }

  // 向量点乘
  double Dot(const Point2d& v) const
  {
    return x * v.x + y * v.y;
  }

  // 向量的模
  double Mod() const
  {
    return sqrt(x * x + y * y);
  }

  std::string ToString() const
  {
    std::ostringstream ostr;
    ostr << "(" << this->x << "," << this->y << ")";
    return ostr.str();
  }

  double x, y;
};
