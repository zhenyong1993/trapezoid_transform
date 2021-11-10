#include "Quadrilateral.h"

std::vector<Point2D> Quadrilateral::GetSections(const Point2D& a, const Point2D& b, unsigned int n)
{
    std::vector<Point2D> sections;

    if (n == 0) {
        return sections;
    }

    sections.push_back(a);
    if (a.Equals(b)) {
        return sections;
    }

    double x, y;
    int i = 1;
    for(; i <= n -1; i++) {
        x = (b.x - a.x) * i / n + a.x;
        y = (b.y - a.y) * i / n + a.y;
        sections.push_back(Point2D(x, y));
    }

    return sections;
}
