#include "Quadrilateral.h"

// 经过p点，斜率为k的直线和四边形的交点, isVertical为true表示直线斜率为无穷大，此时忽略k
std::vector<Point2d> Quadrilateral::LineIntersections(const Point2d& p, float k, bool isVertical/* = false*/)
{
    std::vector<Point2d> intersections;

    // Geometry::CalPointFromLineWithDistance(p, k)

    return intersections;
}

std::vector<Point2d> MaxInnerRect(const Point2d&p, float aspectRatio)
{
    std::vector<Point2d> vertices;

    // assert(vertices.size() == 2)
    return vertices;
}

std::vector<Point2d> MaxInnerRect(float aspectRatio)
{
    std::vector<Point2d> vertices;

    // assert(vertices.size() == 4)
    return vertices;
}
