#include "Quadrilateral.h"
#include "Geometry.h"

// 经过p点，斜率为k的直线和四边形的交点, isVertical为true表示直线斜率为无穷大，此时忽略k，如果p点为四边形的顶点，返回的数组中可能有多个重复的p点
std::vector<Point2d> Quadrilateral::LineIntersections(const Point2d& p, double k, bool isVertical/* = false*/)
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
std::vector<Point2d> Quadrilateral::MaxInnerRect(const Point2d&p, double aspectRatio)
{
    std::vector<Point2d> vertices;

    if (!IsPointInEdges(p)) {
        return vertices;
    }

    std::vector<Point2d> horizontal_points = LineIntersections(p, 0);
    std::vector<Point2d> vertical_points = LineIntersections(p, 0, true);

    if ((horizontal_points.size() < 2) || (vertical_points.size() < 2)) {
        // todo: impossible??????
        return vertices;
    }

    Point2d horizontal_point, vertical_point, diagonal_point;
    double curr_dis;
    bool isValid = false;
    double maxDis = 0.0;
    for (auto tmp_point: horizontal_points) {
        curr_dis = tmp_point.Distance(p);
        if (curr_dis > maxDis) {
            horizontal_point = tmp_point;
            maxDis = curr_dis;
            isValid = true;
        }
    }
    if (!isValid) {
        return vertices;
    }

    isValid = false;
    maxDis = 0.0;
    for (auto tmp_point: vertical_points) {
        curr_dis = tmp_point.Distance(p);
        if (curr_dis > maxDis) {
            vertical_point = tmp_point;
            maxDis = curr_dis;
            isValid = true;
        }
    }
    if (!isValid) {
        return vertices;
    }

    Point2d v1{horizontal_point.x - p.x, horizontal_point.y - p.y};
    Point2d v2{vertical_point.x - p.x, vertical_point.y - p.y};
    Point2d v3 = v1 + v2;
    // 判断斜率为k还是-k
    double slope = (v3.x * v3.y > 0) ? (1 / aspectRatio) : (-1 / aspectRatio);
    
    std::vector<Point2d> diagonal_points = LineIntersections(p, slope);
    if (diagonal_points.size() < 2) {
        // todo: impossible???????
        return vertices;
    }

    isValid = false;
    maxDis = 0.0;
    for (auto tmp_point: diagonal_points) {
        curr_dis = tmp_point.Distance(p);
        if (curr_dis > maxDis) {
            diagonal_point = tmp_point;
            maxDis = curr_dis;
            isValid = true;
        }
    }
    if (!isValid) {
        return vertices;
    }

    double horizontal_aspect = p.Distance(horizontal_point) / aspectRatio;
    double vertical_aspect = p.Distance(vertical_point) / 1.0;
    double diagonal_aspect = p.Distance(diagonal_point) / sqrt(aspectRatio * aspectRatio + 1);

    double min_aspect = horizontal_aspect;
    int min_index = 0;
    if (vertical_aspect < min_aspect) {
        min_index = 1;
        min_aspect = vertical_aspect;
    }
    if (diagonal_aspect < min_aspect) {
        min_index = 2;
        min_aspect = diagonal_aspect;
    }

    if (min_index == 0) {           // horizontal
        vertices.emplace_back(horizontal_point);
        int coeff = 1;
        if (vertical_point.y < p.y) {
            coeff = -1;
        }
        vertices.emplace_back(p.x, p.y + coeff * fabs(horizontal_point.x - p.x) / aspectRatio);
    } else if (min_index == 1) {    // vertical
        int coeff = 1;
        if (horizontal_point.x < p.x) {
            coeff = -1;
        }
        vertices.emplace_back(p.x + coeff * fabs(vertical_point.y - p.y) * aspectRatio, p.y);
        vertices.emplace_back(vertical_point);
    } else {                        // diagonal
        vertices.emplace_back(diagonal_point.x, p.y);
        vertices.emplace_back(p.x, diagonal_point.y);
    }

    return vertices;
}

// 返回四边形最大内接矩形（需保证该外接矩形的两条相邻边中，一条平行与x轴，另一条平行与y轴，并且宽高比为aspectRatio）的四个顶点，
// 顺序为lb(坐下)->rb(右下)->rt(右上)->lt(左上)
std::vector<Point2d> Quadrilateral::MaxInnerRect(double aspectRatio)
{
    std::vector<Point2d> vertices;
    std::vector<Point2d> all_points;        // 四条边上的所有等分点
    std::vector<Point2d> oneline_points;    // 其中一条边上的等分点
    std::vector<Point2d> tmp_points;
    std::vector<Point2d> max_points;        // 最终找到的最大矩形的对角线上的两个点

    // 预先分配最大容量，提高效率
    all_points.reserve(DIVIDE_SECTIONS * 4);
    oneline_points = Geometry::CalSections(this->a, this->b, DIVIDE_SECTIONS);
    all_points.insert(all_points.end(), oneline_points.begin(), oneline_points.end());
    oneline_points = Geometry::CalSections(this->b, this->c, DIVIDE_SECTIONS);
    all_points.insert(all_points.end(), oneline_points.begin(), oneline_points.end());
    oneline_points = Geometry::CalSections(this->c, this->d, DIVIDE_SECTIONS);
    all_points.insert(all_points.end(), oneline_points.begin(), oneline_points.end());
    oneline_points = Geometry::CalSections(this->d, this->a, DIVIDE_SECTIONS);
    all_points.insert(all_points.end(), oneline_points.begin(), oneline_points.end());

    double max_diag = 0.0;
    double tmp_diag;
    for(auto point: all_points) {
        tmp_points = MaxInnerRect(point, aspectRatio);
        if (tmp_points.size() != 2) {
            // todo: impossible????????
            continue;
        }
        tmp_diag = tmp_points[0].Distance(tmp_points[1]);
        if (tmp_diag > max_diag) {
            max_points = tmp_points;
        }
    }

    // todo: 是否需要在max_points对应的直线上的点周围继续寻找更精确的点？

    double minX = std::min(max_points[0].x, max_points[1].x);
    double maxX = std::max(max_points[0].x, max_points[1].x);
    double minY = std::min(max_points[0].y, max_points[1].y);
    double maxY = std::max(max_points[0].y, max_points[1].y);

    vertices.emplace_back(minX, minY);
    vertices.emplace_back(maxX, minY);
    vertices.emplace_back(maxX, maxY);
    vertices.emplace_back(minX, maxY);

    return vertices;
}
