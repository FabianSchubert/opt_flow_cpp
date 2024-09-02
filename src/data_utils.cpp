#include <stdint.h>
#include "data_utils.h"

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