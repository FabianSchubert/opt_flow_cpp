#ifndef OPT_FLOW_H
#define OPT_FLOW_H

#include <stdint.h>

class OptFlow
{
public:
    OptFlow(int _width, int _height, float _tau, float _g_reg, float _alpha_hs, int _kern_half, int _kern_half_hs);
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
    float* u_raw;
    float* v_raw;
    float* u_filt;
    float* v_filt;
    float* t_prev;

    float tau;
    float g_reg;
    float alpha_hs;
    uint8_t kern_half;
    uint8_t kern_half_hs;

    float kern_norm;
    float kern_norm_hs;

    float t_weight(float dt);

    float kern_weight(int dx, int dy);
    float kern_weight_hs(int dx, int dy);
};

#endif // !OPT_FLOW_H