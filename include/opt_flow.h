#ifndef OPT_FLOW_H
#define OPT_FLOW_H

#include <stdint.h>

class OptFlow
{
public:
    OptFlow(int _width, int _height);
    ~OptFlow();

    void update_flow(uint32_t *t, uint16_t *x, uint16_t *y, uint8_t *p,
                     float *u, float *v, int n_events);

private:
    int width;
    int height;
    int n_pix;
    float* a_t0;
    float* a_t1;
    float* a_t2;
    float* t_prev;
};

#endif // !OPT_FLOW_H