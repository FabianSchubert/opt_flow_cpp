#include <stdint.h>
#include "opt_flow.h"

OptFlow::OptFlow(int _width, int _height)
{
    width = _width;
    height = _height;
    n_pix = width * height;
    a_t0 = new float[n_pix];
    a_t1 = new float[n_pix];
    a_t2 = new float[n_pix];
    t_prev = new float[n_pix];
};

OptFlow::~OptFlow()
{
    delete[] a_t0;
    delete[] a_t1;
    delete[] a_t2;
    delete[] t_prev;
};

void OptFlow::update_flow(uint32_t *t, uint16_t *x, uint16_t *y, uint8_t *p,
                          float *u, float *v, int n_events)
{
    for (int i = 0; i < n_events; i++)
    {
        u[i] = 0.0;
        v[i] = 0.0;
        // just a dummy implementation
    }
};
