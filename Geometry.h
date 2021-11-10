#pragma once

#include <vector>
#include <cfloat>
#include <cmath>
#include <algorithm>

#include "Point.h"

class Geometry {
public:
    static bool isPointInLine(const Point2D& p, const Point2D& s, const Point2D& e) {
        double d1 = sqrt((p.x - s.x) * (p.x - s.x) + (p.y - s.y) * (p.y - s.y)); 
        double d2 = sqrt((p.x - e.x) * (p.x - e.x) + (p.y - e.y) * (p.y - e.y));
        double d3 = sqrt((s.x - e.x) * (s.x - e.x) + (s.y - e.y) * (s.y - e.y));
        if(fabs(d1 + d2 - d3) <= DBL_EPSILON) {
            return true;
        }
        return false;
    }

    static bool intersection(const Point2D& start1, const Point2D& end1, const Point2D& start2, const Point2D& end2, Point2D& intersection);

private:

    static std::vector<double> getParam(const Point2D& point1, const Point2D& point2) {
        //A = y2-y1, B = x1-x2, C = x2y1-x1y2
        double a = point2.y - point1.y;
        double b = point1.x - point2.x;
        double c = point2.x * point1.y - point1.x * point2.y;
        return std::vector<double>{a, b, c};
    }
};
