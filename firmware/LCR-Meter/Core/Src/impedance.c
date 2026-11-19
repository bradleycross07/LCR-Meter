/* impedance.c */
#include "impedance.h"
#include <math.h>
#define TWO_PI 6.28318531f

phasor_t phasor_from_samples(const uint16_t *samples, uint32_t n, uint32_t stride, uint32_t samples_per_cycle)
{
    phasor_t result = {0.0f, 0.0f};
    float sum_re = 0;
    float sum_im = 0;
    for (uint32_t i = 0; i < n; i++) {
    	float x     = samples[i * stride];
	float angle = TWO_PI * i / samples_per_cycle;
	sum_re += x * cosf(angle);
	sum_im -= x * sinf(angle);
    }
    result.re = sum_re * 2 / n;
    result.im = sum_im * 2 / n;
    return result;
}

impedance_t impedance_from_phasors(phasor_t v_in, phasor_t v_out, float r_f)
{
   impedance_t result = {0.0f, 0.0f}; /* result being 'z' */
   
   float denom = v_out.re * v_out.re + v_out.im * v_out.im;
   
   result.r = -r_f * (v_in.re * v_out.re + v_in.im * v_out.im) / denom;
   result.x = -r_f * (v_in.im * v_out.re - v_in.re * v_out.im) / denom;
   
   return result;
}

float capacitance_from_z(impedance_t z, float freq)
{
   float omega = TWO_PI * freq;  /* angular freq in rad/s */
   return -1.0f / (omega * z.x); /* C = -1 / (w * X) */
}

float inductance_from_z(impedance_t z, float freq)
{
  float omega = TWO_PI * freq;
  return z.x / omega; /* L = X / w */
}
