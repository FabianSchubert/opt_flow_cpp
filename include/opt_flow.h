#ifndef OPT_FLOW_H
#define OPT_FLOW_H

#include <cstdint>

class OptFlow
{
public:
    OptFlow(int _width, int _height, float _tau, float _g_reg, float _alpha_hs, uint8_t _kern_half, uint8_t _kern_half_hs);
    ~OptFlow();

    void update_flow(const uint32_t *t, const uint16_t *x, const uint16_t *y, const uint8_t *p,
                     float *u, float *v, int n_events) const;

private:
    int width;
    int height;
    int n_pix;

    float* a_t0_p;
    float* a_t1_p;
    float* a_t2_p;
    float* a_t0_n;
    float* a_t1_n;
    float* a_t2_n;

    float* u_raw;
    float* v_raw;
    float* u_filt_p;
    float* v_filt_p;
    float* u_filt_n;
    float* v_filt_n;

    float* t_prev_p;
    float* t_prev_n;

    float tau;
    float g_reg;
    float alpha_hs;
    uint8_t kern_half;
    uint8_t kern_half_hs;
    uint16_t kern_size;
    uint16_t kern_size_hs;

    float kern_norm;
    float kern_norm_hs;

    float t_weight(float dt) const;

    float kern_weight(int dx, int dy) const;
    float kern_weight_hs(int dx, int dy) const;
};

#endif // !OPT_FLOW_H
