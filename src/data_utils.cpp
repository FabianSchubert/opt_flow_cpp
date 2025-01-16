#include <cstdint>
#include "data_utils.h"
#include "viz.h"

void update_event_pixels(const uint16_t *x, const uint16_t *y, const uint8_t *p,
                         uint8_t tex_data[], const int n_events, const int n_pix, const int width, int height)
{
  for (int i = 0; i < n_events; i++)
  {
    int idx = x[i] + y[i] * width;
    if (idx < n_pix)
    {
      tex_data[idx * 4] = 255;
      tex_data[idx * 4 + 1] = 0;
      tex_data[idx * 4 + 2] = 255 * p[i];
      tex_data[idx * 4 + 3] = (1 - p[i]) * 255;
    }
  }
};

void update_flow_pixels(const uint16_t *x, const uint16_t *y, const float *u, const float *v, uint8_t tex_data[],
                        const int n_events, const int n_pix, const int width, int height, const float scale)
{
  for (int i = 0; i < n_events; i++)
  {
    if (const int idx = x[i] + y[i] * width; idx < n_pix)
    {
      int r, g, b;
      vect_to_rgb(u[i], v[i], r, g, b, scale);
      tex_data[idx * 4] = 255;
      tex_data[idx * 4 + 1] = static_cast<uint8_t>(b);
      tex_data[idx * 4 + 2] = static_cast<uint8_t>(g);
      tex_data[idx * 4 + 3] = static_cast<uint8_t>(r);
    }
  }
};