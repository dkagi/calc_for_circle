#ifndef ALL_MATH_H
#define ALL_MATH_H

#include <QPointF>
#include <vector>

struct Circle {
    QPointF center;
    double radius;
};

class all_math
{
public:
    all_math();

    static Circle find_min_circle(std::vector<QPointF> points);

private:
    static double distance(QPointF a, QPointF b);
    static bool inside(const Circle& c, QPointF p);
    static Circle circle_from_two_points(QPointF a, QPointF b);
    static Circle circle_from_three_points(QPointF a, QPointF b, QPointF c);
    static Circle min_disk(const std::vector<QPointF>& points, int n, std::vector<QPointF> boundary);
};

#endif // ALL_MATH_H
