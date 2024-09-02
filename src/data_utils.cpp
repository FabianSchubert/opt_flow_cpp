#include <stdint.h>
#include "data_utils.h"
#include "viz.h"

void update_event_pixels(uint16_t *x, uint16_t *y, uint8_t *p,
                         uint8_t tex_data[], int n_events, int n_pix, int width, int height)
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

void update_flow_pixels(uint16_t *x, uint16_t *y, float *u, float *v, uint8_t tex_data[],
                        int n_events, int n_pix, int width, int height, float scale)
{
  for (int i = 0; i < n_events; i++)
  {
    int idx = x[i] + y[i] * width;
    if (idx < n_pix)
    {
      int r, g, b;
      vect_to_rgb(u[i], v[i], r, g, b, scale);
      tex_data[idx * 4] = 255;
      tex_data[idx * 4 + 1] = (uint8_t)(b);
      tex_data[idx * 4 + 2] = (uint8_t)(g);
      tex_data[idx * 4 + 3] = (uint8_t)(r);
    }
  }
};