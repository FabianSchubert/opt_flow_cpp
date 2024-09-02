#include <stdint.h>
#include <math.h>
#include <iostream>
#include "opt_flow.h"


OptFlow::OptFlow(int _width, int _height, float _tau, float _g_reg, int _kern_half)
{
    width = _width;
    height = _height;
    n_pix = width * height;

    a_t0 = new float[n_pix];
    a_t1 = new float[n_pix];
    a_t2 = new float[n_pix];
    t_prev = new float[n_pix];

    tau = _tau;
    g_reg = _g_reg;
    kern_half = (uint8_t)(_kern_half);
    std::cout << "kern_half: " << (int)kern_half << std::endl;
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
        int idx = x[i] + y[i] * width;
        if (idx < n_pix)
        {
            float dt = (t[i] - t_prev[idx])/1000.0;
            float wt = t_weight(dt);

            a_t2[idx] = wt * (dt * dt * a_t0[idx] + 2 * dt * a_t1[idx] + a_t2[idx]);
            a_t1[idx] = wt * (dt * a_t0[idx] + a_t1[idx]);
            a_t0[idx] = wt * a_t0[idx] + 1;

            t_prev[idx] = t[i];

            float _alpha_x = 0.0;
            float _alpha_y = 0.0;
            float _beta = 0.0;

            for(int dx = -kern_half; dx < kern_half + 1; dx++){
                for(int dy = -kern_half; dy < kern_half + 1; dy++){
                    float wx = kern_weight(dx, dy);
                    int idx2 = x[i] + dx + (y[i] + dy) * width;
                    if(idx2 < n_pix){
                        float dt = (t[i] - t_prev[idx2])/1000.0;
                        float wt = t_weight(dt);
                        _alpha_x += -wx * wt * dx * (dt * a_t0[idx2] + a_t1[idx2]);
                        _alpha_y += -wx * wt * dy * (dt * a_t0[idx2] + a_t1[idx2]);

                        _beta += wx * wt * (dt * dt * a_t0[idx2] + 2 * dt * a_t1[idx2] + a_t2[idx2]);
                    }
                }
            }
            u[i] = _alpha_x / (_beta + g_reg);
            v[i] = _alpha_y / (_beta + g_reg);
        }
    }
};

float OptFlow::t_weight(float dt)
{
    return exp(-dt / tau) * (dt >= 0);
};

float OptFlow::kern_weight(int dx, int dy)
{
    return exp(-(dx * dx + dy * dy) / (2 * 0.09 * kern_half * kern_half));
};