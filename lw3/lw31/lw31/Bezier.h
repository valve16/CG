#pragma once

#include <vector>
#include <utility>

class CBezier
{
public:
    using Point = std::pair<float, float>;

    CBezier();
    const std::vector<Point>& GetControlPoints() const;
    void SetControlPoint(size_t index, const Point& point);

private:
    std::vector<Point> m_controlPoints;
};

