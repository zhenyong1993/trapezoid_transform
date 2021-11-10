#include <iostream>

#include "Geometry.h"
#include "Quadrilateral.h"

int main()
{
    // Point2D start1 = {0, 0}, end1 = {1, 1};
    // Point2D start2 = {0, 1}, end2 = {1, 0};
    // Point2D p;
    // bool ret = Geometry::intersection(start1, end1, start2, end2, p);
    // if (ret) {
    //     std::cout << p.x << ", " << p.y << std::endl;
    // } else {
    //     std::cout << "no intersection" << std::endl;
    // }

    Point2D a{0, 1};
    Point2D b{0, 0};
    Point2D c{1, 0};
    Point2D d{1, 1};
    Quadrilateral q(a, b, c, d);

    // std::cout << q.ToString() << " is " << (q.IsConvex() ? "" : "not ") << "convex" << std::endl;

    auto sections = Quadrilateral::GetSections(a, b, 3);
    for(Point2D section: sections) {
        std::cout << section.ToString() << std::endl;
    }

    return 0;
}
