#include "Quadrilateral.h"

// 经过p点，斜率为k的直线和四边形的交点, isVertical为true表示直线斜率为无穷大，此时忽略k
std::vector<Point2D> Quadrilateral::LineIntersections(const Point2D& p, bool isVertical, float k)
{
    std::vector<Point2D> intersections;

    return intersections;
}

std::vector<Point2D> MaxInnerRect(const Point2D&p, float aspectRatio)
{
    std::vector<Point2D> vertices;

    // assert(vertices.size() == 2)
    return vertices;
}

std::vector<Point2D> MaxInnerRect(float aspectRatio)
{
    std::vector<Point2D> vertices;

    // assert(vertices.size() == 4)
    return vertices;
}
