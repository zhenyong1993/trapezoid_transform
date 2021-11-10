#include "Geometry.h"

bool Geometry::intersection(const Point2D& start1, const Point2D& end1, const Point2D& start2, const Point2D& end2, Point2D& intersection) {
    int dx1 = end1.x - start1.x;
    int dy1 = end1.y - start1.y;

    int dx2 = end2.x - start2.x;
    int dy2 = end2.y - start2.y;

    if(dx1*dy2 == dx2*dy1) {
        return false;
    }

    std::vector<double> p1 = getParam(start1, end1);
    std::vector<double> p2 = getParam(start2, end2);

    double x = double(p2[2] * p1[1] - p1[2] * p2[1]) / double(p1[0] * p2[1] - p2[0] * p1[1]);
    double y = double(p1[2] * p2[0] - p2[2] * p1[0]) / double(p1[0] * p2[1] - p2[0] * p1[1]);

    Point2D point{x, y};
    if(isPointInLine(point, start1, end1) && isPointInLine(point, start2, end2)) {
        intersection = point;
        return true;
    }
    return false;
}
