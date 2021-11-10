#pragma once

#include <vector>
#include <sstream>

#include "Point.h"

class Quadrilateral {
public:
    // a, b, c, d按逆时针顺序
    Quadrilateral(const Point2D& a, const Point2D& b, const Point2D& c, const Point2D& d) {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
    }

    std::string ToString() const {
        std::ostringstream ostr;
        ostr << "(" << a.x << "," << a.y << "),(" << b.x << "," << b.y << "),(" << c.x << "," << c.y << "),(" << d.x << "," << d.y << ")";
        return ostr.str();
    }

    // https://blog.csdn.net/Coding_Dreaming/article/details/50709640
    bool IsConvex() const {
        double t1 = (d.x - a.x) * (b.y - a.y) - (d.y - a.y) * (b.x - a.x);
        double t2 = (a.x - b.x) * (c.y - b.y) - (a.y - b.y) * (c.x - b.x);
        double t3 = (b.x - c.x) * (d.y - c.y) - (b.y - c.y) * (d.x - c.x);
        double t4 = (c.x - d.x) * (a.y - d.y) - (c.y - d.y) * (a.x - d.x);

        return (t1 * t2 * t3 * t4 > 0);
    }

    // a和b组成的线段n等分，输出等分点(如果a,b重合，输出a点，如果不重合，输出从a开始的n个点)
    static std::vector<Point2D> GetSections(const Point2D& a, const Point2D& b, unsigned int n);

private:
    Point2D a, b, c, d;
};
