#include <stdint.h>
#include <math.h>
#include <iostream>
#include <omp.h>
#include "opt_flow.h"


OptFlow::OptFlow(int _width, int _height, float _tau, float _g_reg, float _alpha_hs, int _kern_half, int _kern_half_hs)
{
    width = _width;
    height = _height;
    n_pix = width * height;

    a_t0 = new float[n_pix];
    a_t1 = new float[n_pix];
    a_t2 = new float[n_pix];
    u_raw = new float[n_pix];
    v_raw = new float[n_pix];
    u_filt = new float[n_pix];
    v_filt = new float[n_pix];
    t_prev = new float[n_pix];

    for(int i = 0; i < n_pix; i++){
        a_t0[i] = 0.0;
        a_t1[i] = 0.0;
        a_t2[i] = 0.0;
        u_raw[i] = 0.0;
        v_raw[i] = 0.0;
        u_filt[i] = 0.0;
        v_filt[i] = 0.0;
        t_prev[i] = 0.0;
    }

    tau = _tau;
    g_reg = _g_reg;
    alpha_hs = _alpha_hs;
    kern_half = (uint8_t)(_kern_half);
    kern_size = (uint16_t)((2 * kern_half + 1) * (2 * kern_half + 1));
    kern_half_hs = (uint8_t)(_kern_half_hs);
    kern_size_hs = (uint16_t)((2 * kern_half_hs + 1) * (2 * kern_half_hs + 1));

    kern_norm = 0.0;
    for(int dx = -kern_half; dx < kern_half + 1; dx++){
        for(int dy = -kern_half; dy < kern_half + 1; dy++){
            kern_norm += kern_weight(dx, dy);
        }
    }

    kern_norm_hs = 0.0;
    for(int dx = -kern_half_hs; dx < kern_half_hs + 1; dx++){
        for(int dy = -kern_half_hs; dy < kern_half_hs + 1; dy++){
            kern_norm_hs += kern_weight_hs(dx, dy);
        }
    }
};

OptFlow::~OptFlow()
{
    delete[] a_t0;
    delete[] a_t1;
    delete[] a_t2;
    delete[] u_raw;
    delete[] v_raw;
    delete[] u_filt;
    delete[] v_filt;
    delete[] t_prev;
};

void OptFlow::update_flow(uint32_t *t, uint16_t *x, uint16_t *y, uint8_t *p,
                          float *u, float *v, int n_events)
{
    //#pragma omp parallel for
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

            
            for(int j=0; j<kern_size;j++){
                //std::cout << omp_get_thread_num() << std::endl;
                int dx = j % (2 * kern_half + 1) - kern_half;
                int dy = j / (2 * kern_half + 1) - kern_half;

                float wx = kern_weight(dx, dy) / kern_norm;
                int idx2 = x[i] + dx + (y[i] + dy) * width;
                if(idx2 > 0 && idx2 < n_pix){
                    float dt = (t[i] - t_prev[idx2])/1000.0;
                    float wt_pair = t_weight(dt);
                    _alpha_x += -wx * wt_pair * dx * (dt * a_t0[idx2] + a_t1[idx2]);
                    _alpha_y += -wx * wt_pair * dy * (dt * a_t0[idx2] + a_t1[idx2]);

                    _beta += wx * wt_pair * (dt * dt * a_t0[idx2] + 2 * dt * a_t1[idx2] + a_t2[idx2]);
                }
            }

            /*
            for(int dx = -kern_half; dx < kern_half + 1; dx++){
                for(int dy = -kern_half; dy < kern_half + 1; dy++){
                    if(dx == 0 && dy == 0){
                        continue;
                    }
                    float wx = kern_weight(dx, dy) / kern_norm;
                    int idx2 = x[i] + dx + (y[i] + dy) * width;
                    if(idx2 > 0 && idx2 < n_pix){
                        float dt = (t[i] - t_prev[idx2])/1000.0;
                        float wt_pair = t_weight(dt);
                        _alpha_x += -wx * wt_pair * dx * (dt * a_t0[idx2] + a_t1[idx2]);
                        _alpha_y += -wx * wt_pair * dy * (dt * a_t0[idx2] + a_t1[idx2]);

                        _beta += wx * wt_pair * (dt * dt * a_t0[idx2] + 2 * dt * a_t1[idx2] + a_t2[idx2]);
                    }
                }
            }*/

            //u[i] = 1000.0 * _alpha_x / (_beta + g_reg); // x 1000 to get output in pixels per second
            //v[i] = 1000.0 * _alpha_y / (_beta + g_reg);

            
            u_raw[idx] = _alpha_x / (_beta + g_reg);
            v_raw[idx] = _alpha_y / (_beta + g_reg);

            //u_t0[idx] = wt * u_t0[idx] + u[i];
            //v_t0[idx] = wt * v_t0[idx] + v[i];
            
            float u_hs = 0.0;
            float v_hs = 0.0;
            float beta_hs = 0.0;

            for(int dx = -kern_half_hs; dx < kern_half_hs + 1; dx++){
                for(int dy = -kern_half_hs; dy < kern_half_hs + 1; dy++){
                    float wx = kern_weight_hs(dx, dy) / kern_norm_hs;
                    int idx2 = x[i] + dx + (y[i] + dy) * width;
                    if(idx2 > 0 && idx2 < n_pix){
                        float dt = (t[i] - t_prev[idx2])/1000.0;
                        float wt_pair = t_weight(dt);
                        u_hs += wx * wt_pair * u_filt[idx2];
                        v_hs += wx * wt_pair * v_filt[idx2];

                        beta_hs += wx * wt_pair;
                    }
                }
            }

            u_hs = u_hs / (beta_hs + 1e-8);
            v_hs = v_hs / (beta_hs + 1e-8);
            
            float l_raw = sqrt(u_raw[idx] * u_raw[idx] + v_raw[idx] * v_raw[idx]) + 1e-8;
            
            float hs_dotraw = (u_hs * u_raw[idx] + v_hs * v_raw[idx]) / l_raw;

            float u_hs_proj = 0.2 * (u_hs + (l_raw - hs_dotraw) * u_raw[idx] / l_raw) + 0.8 * u_hs;
            float v_hs_proj = 0.2 * (v_hs + (l_raw - hs_dotraw) * v_raw[idx] / l_raw) + 0.8 * v_hs;

            u_filt[idx] = u_hs_proj;
            v_filt[idx] = v_hs_proj;

            u[i] = 1000.0 * u_filt[idx];
            v[i] = 1000.0 * v_filt[idx];

            //u[i] = 1000.0 * u_raw[idx];
            //v[i] = 1000.0 * v_raw[idx];

            //u[i] = 1000.0 * _alpha_x / (_beta + g_reg); // x 1000 to get output in pixels per second
            //v[i] = 1000.0 * _alpha_y / (_beta + g_reg);
            
            
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

float OptFlow::kern_weight_hs(int dx, int dy)
{
    return exp(-(dx * dx + dy * dy) / (2 * 0.09 * kern_half_hs * kern_half_hs));
};