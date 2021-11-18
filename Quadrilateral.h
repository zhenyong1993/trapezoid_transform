#pragma once

#include <vector>
#include <sstream>
#include <algorithm>

#include "Point.h"

class Quadrilateral {
public:
    // a, b, c, d按逆时针顺序
    Quadrilateral(const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d) {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;

        minX = std::min({a.x, b.x, c.x, d.x});
        maxX = std::max({a.x, b.x, c.x, d.x});
        minY = std::min({a.y, b.y, c.y, d.y});
        maxY = std::max({a.y, b.y, c.y, d.y});

        A = {minX, maxY};
        B = {minX, minY};
        C = {maxX, minY};
        D = {maxX, maxY};
    }

    std::string ToString() const {
        std::ostringstream ostr;
        ostr << "(" << a.x << "," << a.y << "),(" << b.x << "," << b.y << "),(" << c.x << "," << c.y << "),(" << d.x << "," << d.y << ")";
        return ostr.str();
    }

    // 返回四边形最大内接矩形（需保证该外接矩形的两条相邻边中，一条平行与x轴，另一条平行与y轴，并且宽高比为aspectRatio）的四个顶点，
    // 顺序为lb(坐下)->rb(右下)->rt(右上)->lt(左上)
    std::vector<Point2d> MaxInnerRect(double aspectRatio);
public:  //todo: 为方便单元测试，暂时改为public，最终改为private
    // 经过p点，斜率为k的直线和四边形的交点, isVertical为true表示直线斜率为无穷大，此时忽略k，如果p点为四边形的顶点，返回的数组中可能有多个重复的p点
    std::vector<Point2d> LineIntersections(const Point2d& p, double k, bool isVertical = false);
    // p是四边行上的点，返回经过该点的最大内接矩形（需保证该外接矩形的两条相邻边中，一条平行与x轴，另一条平行与y轴，并且宽高比为aspectRatio）的
    // 两个和p点相邻的顶点(第一个顶点的y坐标和p点相等，第二个顶点的x坐标和p点相等)
    std::vector<Point2d> MaxInnerRect(const Point2d&p, double aspectRatio);

    // https://blog.csdn.net/Coding_Dreaming/article/details/50709640
    bool IsConvex() {
        static bool isFirst = true;
        if (isFirst) {
            double t1 = (d.x - a.x) * (b.y - a.y) - (d.y - a.y) * (b.x - a.x);
            double t2 = (a.x - b.x) * (c.y - b.y) - (a.y - b.y) * (c.x - b.x);
            double t3 = (b.x - c.x) * (d.y - c.y) - (b.y - c.y) * (d.x - c.x);
            double t4 = (c.x - d.x) * (a.y - d.y) - (c.y - d.y) * (a.x - d.x);
            isConvex = (t1 * t2 * t3 * t4 > 0);
            isFirst = false;
        }
        return isConvex;
    }

    // 判断p点是否在四边形的边上
    bool IsPointOnEdges(const Point2d&p);

    // 四边形的四个顶点，按逆时针顺序
    Point2d a, b, c, d;
    // 四边形最小外接矩形的四个顶点(需保证该外接矩形的两条相邻边中，一条平行与x轴，另一条平行与y轴)
    Point2d A, B, C, D;
    // 分别表示四个点中的x坐标的最小值, x坐标的最大值, y坐标的最小值，ｙ坐标的最大值
    double minX, maxX, minY, maxY;

    bool isConvex = false;

    static constexpr unsigned int DIVIDE_SECTIONS = 1000;
    static constexpr unsigned long INFINITY_DISTANCE = 1000000;
};
