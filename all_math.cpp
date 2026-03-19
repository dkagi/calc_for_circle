#include "all_math.h"
#include <QPointF>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

all_math::all_math() {}

double all_math::distance(QPointF a, QPointF b){
    return std::sqrt(std::pow(a.x() - b.x(), 2) + std::pow(a.y() - b.y(), 2));
}

bool all_math::inside(const Circle& c, QPointF p){
    return distance(c.center, p) <= c.radius;
}

Circle all_math::circle_from_two_points(QPointF a, QPointF b){
    QPointF center = (a + b) / 2.0;
    return {center, distance(a, b) / 2.0};
}

Circle all_math::circle_from_three_points(QPointF a, QPointF b, QPointF c){
    double x1 = a.x(), y1 = a.y();
    double x2 = b.x(), y2 = b.y();
    double x3 = c.x(), y3 = c.y();

    double D = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
    if (std::abs(D) < 1e-9)
        return {{0,0}, 0};

    double centerX = ((x1*x1 + y1*y1) * (y2 - y3) + (x2*x2 + y2*y2) * (y3 - y1) + (x3*x3 + y3*y3) * (y1 - y2)) / D;
    double centerY = ((x1*x1 + y1*y1) * (x3 - x2) + (x2*x2 + y2*y2) * (x1 - x3) + (x3*x3 + y3*y3) * (x2 - x1)) / D;

    QPointF center(centerX, centerY);
    return {center, distance(center, a)};
}

Circle all_math::min_disk(const std::vector<QPointF>& points, int n, std::vector<QPointF> boundary){
    if (n==0 || boundary.size()==3){
        if (boundary.empty())
            return {{0,0},0};
        if (boundary.size() == 1)
            return {boundary[0], 0};
        if (boundary.size() == 2)
            return circle_from_two_points(boundary[0], boundary[1]);
        return circle_from_three_points(boundary[0],boundary[1],boundary[2]);
    }
    QPointF p = points[n - 1];
    Circle d = min_disk(points, n - 1, boundary);

    if (inside(d, p)) {
        return d;
    }

    boundary.push_back(p);
    return min_disk(points, n - 1, boundary);
}

Circle all_math::find_min_circle(std::vector<QPointF> points){
    auto rd = std::random_device {};
    auto rng = std::default_random_engine { rd() };
    std::shuffle(points.begin(), points.end(), rng);

    return min_disk(points, points.size(),{});
}





























