#pragma once

#include <cfloat>
#include <cmath>
#include <string>
#include <sstream>

class Point2D {
public:
    double x;
    double y;

    Point2D(): x(0.0), y(0.0) {}

    Point2D(double x, double y) {
        this->x = x;
        this->y = y;
    }

    bool Equals(double x, double y) const {
        return ((fabs(this->x - x) <= DBL_EPSILON) && (fabs(this->y - y) <= DBL_EPSILON));
    }

    bool Equals(const Point2D& p) const {
        return Equals(p.x, p.y);
    }

    std::string ToString() {
        std::ostringstream ostr;
        ostr << "(" << this->x << "," << this->y << ")";
        return ostr.str();
    }
};
