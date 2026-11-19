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
