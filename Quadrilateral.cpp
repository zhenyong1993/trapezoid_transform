#include "Quadrilateral.h"

#include <cassert>
#include <iostream> // todo: remove

#include "Geometry.h"

// 经过p点，斜率为k的直线和四边形的交点, isVertical为true表示直线斜率为无穷大，此时忽略k
std::vector<Point2d> Quadrilateral::LineIntersections(const Point2d& p, float k, bool isVertical/* = false*/)
{
    std::vector<Point2d> intersections;

    std::vector<Point2d> points = Geometry::CalPointFromLineWithDistance(p, isVertical, k, static_cast<double>(UINT32_MAX));
    if (points.size() != 2) {
        return intersections;
    }

    Point2d intersection;
    if (Geometry::Intersection(points[0], points[1], this->a, this->b, intersection)) {
        intersections.emplace_back(intersection);
    }
    if (Geometry::Intersection(points[0], points[1], this->b, this->c, intersection)) {
        intersections.emplace_back(intersection);
    }
    if (Geometry::Intersection(points[0], points[1], this->c, this->d, intersection)) {
        intersections.emplace_back(intersection);
    }
    if (Geometry::Intersection(points[0], points[1], this->d, this->a, intersection)) {
        intersections.emplace_back(intersection);
    }

    return intersections;
}

bool Quadrilateral::IsPointInEdges(const Point2d&p)
{
    return (Geometry::IsPointInLine(p, this->a, this->b) || Geometry::IsPointInLine(p, this->b, this->c) ||
            Geometry::IsPointInLine(p, this->c, this->d) || Geometry::IsPointInLine(p, this->d, this->a));
}

// p是四边行上的点，返回经过该点的最大内接矩形（需保证该外接矩形的两条相邻边中，一条平行与x轴，另一条平行与y轴，并且宽高比为aspectRatio）的
// 两个和p点相邻的顶点(第一个顶点的y坐标和p点相等，第二个顶点的x坐标和p点相等)
std::vector<Point2d> Quadrilateral::MaxInnerRect(const Point2d&p, float aspectRatio)
{
    std::vector<Point2d> vertices;

    if (!IsPointInEdges(p)) {
        return vertices;
    }

    // assert(vertices.size() == 2)
    return vertices;
}

// 返回四边形最大内接矩形（需保证该外接矩形的两条相邻边中，一条平行与x轴，另一条平行与y轴，并且宽高比为aspectRatio）的四个顶点，
// 顺序为lb(坐下)->rb(右下)->rt(右上)->lt(左上)
std::vector<Point2d> Quadrilateral::MaxInnerRect(float aspectRatio)
{
    std::vector<Point2d> vertices;

    // assert(vertices.size() == 4)
    return vertices;
}
