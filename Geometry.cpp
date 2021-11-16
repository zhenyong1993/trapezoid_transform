#include "Geometry.h"

bool Geometry::Intersection(const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d, Point2d& p) {
    double dx1 = b.x - a.x;
    double dy1 = b.y - a.y;

    double dx2 = d.x - c.x;
    double dy2 = d.y - c.y;

    if(fabs(dx1*dy2 - dx2*dy1) <= EPSILON) {
        return false;
    }

    std::vector<double> p1 = GetParam(a, b);
    std::vector<double> p2 = GetParam(c, d);

    double x = double(p2[2] * p1[1] - p1[2] * p2[1]) / double(p1[0] * p2[1] - p2[0] * p1[1]);
    double y = double(p1[2] * p2[0] - p2[2] * p1[0]) / double(p1[0] * p2[1] - p2[0] * p1[1]);

    Point2d point{x, y};
    if(IsPointInLine(point, a, b) && IsPointInLine(point, c, d)) {
        p = point;
        return true;
    }
    return false;
}

// a和b组成的线段n等分，输出等分点(如果a,b重合，输出a点，如果不重合，输出从a开始的n个点)
std::vector<Point2d> Geometry::CalSections(const Point2d& a, const Point2d& b, unsigned int n)
{
    std::vector<Point2d> sections;

    if (n == 0) {
        return sections;
    }

    sections.emplace_back(a);
    if (a.Equals(b)) {
        return sections;
    }

    double x, y;
    int i = 1;
    for(; i <= n -1; i++) {
        x = (b.x - a.x) * i / n + a.x;
        y = (b.y - a.y) * i / n + a.y;
        sections.emplace_back(Point2d(x, y));
    }

    return sections;
}

// ab射线上与点a距离为d的点p
bool Geometry::CalPointFromLineWithDistance(const Point2d& a, const Point2d& b, double d, Point2d& p)
{
    if (a == b || d < 0) {
        return false;
    }

    Point2d D = b - a;
    double t = d / D.Mod();
    p = a + D.Scalar(t);

    return true;
}

// 经过p且斜率为k(如果isVertical为true，表示斜率为无穷大)的直线上与点a距离为d的点
std::vector<Point2d> Geometry::CalPointFromLineWithDistance(const Point2d& p, bool isVertical, double k, double d)
{
    std::vector<Point2d> points;

    if (d < 0.0) {
        return points;
    } else if (d <= EPSILON) {
        points.emplace_back(p);
        return points;
    }

    Point2d p1, p2;

    // p1和p2分别是直线上和a在两端的两个点
    if (!isVertical) {
        p1.Set(p.x + 1, k + p.y);
        p2.Set(p.x - 1, -k + p.y);
    } else {
        p1.Set(p.x, p.y + 1);
        p2.Set(p.x, p.y - 1);
    }

    Point2d p3, p4;
    if (CalPointFromLineWithDistance(p, p1, d, p3)) {
        points.emplace_back(p3);
    }
    if (CalPointFromLineWithDistance(p, p2, d, p4)) {
        points.emplace_back(p4);
    }

    return points;
}
