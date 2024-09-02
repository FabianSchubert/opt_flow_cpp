#include <math.h>
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

void vect_to_rgb(float u, float v, int &r, int &g, int &b, float scale)
{
    float angle = atan2(v, u);
    float magnitude = std::min(1.0f, sqrt(u * u + v * v) / scale);

    float hue = (angle + M_PI) / (2 * M_PI);

    r = (int)(magnitude * (clamp2<float>(2.0 - 6.0 * hue, 0.0, 1.0) + clamp2<float>(6.0 * hue - 4.0, 0.0, 1.0)) * 255);
    g = (int)(magnitude * clamp2<float>(6.0 * hue, 0.0, 1.0) * clamp2<float>(4.0 - 6.0 * hue, 0.0, 1.0) * 255);
    b = (int)(magnitude * clamp2<float>(6.0 * hue - 2.0, 0.0, 1.0) * clamp2<float>(6.0 - 6.0 * hue, 0.0, 1.0) * 255);
}