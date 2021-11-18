#include <iostream>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "Geometry.h"
#include "Quadrilateral.h"

int main()
{
    // Point2d start1 = {0, 0}, end1 = {1, 1};
    // Point2d start2 = {0, 1}, end2 = {1, 0};
    // Point2d p;
    // bool ret = Geometry::Intersection(start1, end1, start2, end2, p);
    // if (ret) {
    //     std::cout << p.x << ", " << p.y << std::endl;
    // } else {
    //     std::cout << "no Intersection" << std::endl;
    // }

    // Point2d a{0, 1};
    // Point2d b{0, 0};
    // Point2d c{1, 0};
    // Point2d d{1, 1};
    // Quadrilateral q(a, b, c, d);

    // // std::cout << q.ToString() << " is " << (q.IsConvex() ? "" : "not ") << "convex" << std::endl;

    // auto sections = Geometry::CalSections(a, b, 3);
    // for(Point2d section: sections) {
    //     std::cout << section.ToString() << std::endl;
    // }


	// Point2d a(0, 0);
	// Point2d b(1, 1);
	// double d = 5;
	// Point2d p;

	// if (Geometry::CalPointFromLineWithDistance(a, b, d, p)) {
    //     std::cout << "计算的点为：" << p.x << ", " << p.y << std::endl; 
    //     std::cout << "验算距离是否为" << d << "：" << (p-a).Mod() << std::endl;
    // } else {
    //     std::cout << "错误" << std::endl;
    // }

    // Point2d a(1, 1);
	// double d = 5;

    // auto points = Geometry::CalPointFromLineWithDistance(a, false, 1, d);
    // for (auto p: points) {
    //     std::cout << "计算的点为：" << p.x << ", " << p.y << std::endl; 
    // }

    // points = Geometry::CalPointFromLineWithDistance(a, true, 0, d);
    // for (auto p: points) {
    //     std::cout << "计算的点为：" << p.x << ", " << p.y << std::endl; 
    // }

    // Quadrilateral::LineIntersections
    // Quadrilateral quad({0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0});
    // std::cout << "is convex: " << quad.IsConvex() << std::endl;
    // auto intersections = quad.LineIntersections({0.0, 0.5}, 1, false);
    // for(auto p: intersections) {
    //     std::cout << "交点：" << p.x << ", " << p.y << std::endl; 
    // }
    // auto vertices = quad.MaxInnerRect({0.0, 0.5}, 4.0f / 3);
    // for(auto p: vertices) {
    //     std::cout << "顶点：" << p.x << ", " << p.y << std::endl; 
    // }
    // auto vertices = quad.MaxInnerRect(4.0f / 3);
    // for(auto p: vertices) {
    //     std::cout << "顶点：" << p.x << ", " << p.y << std::endl; 
    // }

    auto console = spdlog::stdout_color_st("console");
    console->set_level(spdlog::level::debug);
    // trigger flush whenever errors or more severe messages are logged
    console->flush_on(spdlog::level::err); 

    // auto file_logger = spdlog::basic_logger_st("file_logger", "logs/basic-log.txt");
    // file_logger->set_level(spdlog::level::info);

    // 作为第三方库调用的时候，提供用户设置为file_logger
    spdlog::set_default_logger(console);

    // spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e][T%t][%@.%!][%^%L%$] %v");
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e][T%t][%s:%#:%!][%^%L%$] %v");

    Quadrilateral quad({0.0, 1.0}, {1.0, 0.0}, {2.0, 1.0}, {1.0, 2.0});
    // use default logger
    spdlog::info("Is convex: {}", quad.IsConvex());
    // SPDLOG_LOGGER_INFO(console, "test");
    auto vertices = quad.MaxInnerRect(4.0f / 3);
    for(auto p: vertices) {
        spdlog::info("vertice: {}, {}", p.x, p.y);
    }

    // spdlog::apply_all([&](std::shared_ptr<spdlog::logger> l) { l->info("apply all."); });

    return 0;
}
