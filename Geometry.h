#pragma once

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <vector>

#include "Point.h"

class Geometry {
public:
  // p点是否在se线段上
  static bool IsPointInLine(const Point2d& p, const Point2d& s, const Point2d& e);
  // 计算线段ab和线段cd的交点，如果ab和cd平行或无交点，返回false
  static bool Intersection(const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d, Point2d& p);

  // a和b组成的线段n等分，输出等分点(如果a,b重合，输出a点，如果不重合，输出从a开始的n个点)
  static std::vector<Point2d> CalSections(const Point2d& a, const Point2d& b, unsigned int n);

  // ab射线上与点a距离为d的点p
  static bool CalPointFromLineWithDistance(const Point2d& a, const Point2d& b, double d, Point2d& p);

  // 经过p且斜率为k(如果isVertical为true，表示斜率为无穷大)的直线上与点a距离为d的点
  static std::vector<Point2d> CalPointFromLineWithDistance(const Point2d& p, bool isVertical, double k, double d);

private:
  static std::vector<double> GetParam(const Point2d& point1, const Point2d& point2)
  {
    // A = y2-y1, B = x1-x2, C = x2y1-x1y2
    double a = point2.y - point1.y;
    double b = point1.x - point2.x;
    double c = point2.x * point1.y - point1.x * point2.y;
    return std::vector<double>{a, b, c};
  }
};
