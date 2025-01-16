#include <cmath>
#include <algorithm>
#include "viz.h"

template <typename t>
t clamp2(t x, t min, t max)
{
    if (x < min)
        x = min;
    if (x > max)
        x = max;
    return x;
}

void vect_to_rgb(const float u, const float v, int &r, int &g, int &b, const float scale)
{
    const float angle = std::atan2(v, u);
    const float magnitude = std::min(1.0f, std::sqrt(u * u + v * v) / scale);

    const float hue = (M_PI + angle) / (2 * M_PI);

    r = static_cast<int>(magnitude * (clamp2<float>(2.0 - 6.0 * hue, 0.0, 1.0) + clamp2<float>(6.0f * hue - 4.0f, 0.0f, 1.0f)) *
                         255);
    g = static_cast<int>(magnitude * clamp2<float>(6.0 * hue, 0.0, 1.0) * clamp2<float>(4.0f - 6.0f * hue, 0.0f, 1.0f) * 255);
    b = static_cast<int>(magnitude * clamp2<float>(6.0 * hue - 2.0, 0.0, 1.0) * clamp2<float>(6.0f - 6.0f * hue, 0.0f, 1.0f) * 255);
}