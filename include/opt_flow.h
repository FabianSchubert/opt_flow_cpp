#ifndef OPT_FLOW_H
#define OPT_FLOW_H

#include <stdint.h>

class OptFlow
{
public:
    OptFlow(int _width, int _height, float _tau, float _g_reg, int _kern_half);
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

    float tau;
    float g_reg;
    uint8_t kern_half;

    float t_weight(float dt);

    float kern_weight(int dx, int dy);
};

#endif // !OPT_FLOW_H