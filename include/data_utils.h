#ifndef DATA_UTILS_H
#define DATA_UTILS_H

#include <stdint.h>

// template function for setting all elements of an array to a value
template <typename T>
void set_array(T array[], int n, T value)
{
    for (int i = 0; i < n; i++)
    {
        array[i] = value;
    }
};

void update_event_pixels(const uint16_t *x, const uint16_t *y, const uint8_t *p,
                         uint8_t tex_data[], int n_events, int n_pix, int width, int height);

void update_flow_pixels(const uint16_t *x, const uint16_t *y, const float *u, const float *v, uint8_t tex_data[],
                        int n_events, int n_pix, int width, int height, float scale);

#endif