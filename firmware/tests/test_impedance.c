/* impedance test */
#include <stdio.h>
#include <math.h>
#include "impedance.h"

#define TWO_PI      6.28318531f
#define N           64      /* number of samples */
#define M           16      /* samples per cycle (so 4 cycles) */
#define OFFSET      2048.0f /* mid-scale of the 12-bit ADC */
#define AMPLITUDE   1000.0f
#define PHASE  	    0.5236f   /* 30 degrees, in radians */

int main(void)
{
    uint16_t samples[N];
    for (uint32_t i = 0; i < N; i++) {
    	samples[i] = (uint16_t)(OFFSET + AMPLITUDE * cosf(TWO_PI * i / M + PHASE));
    }
    phasor_t p = phasor_from_samples(samples, N, 1, M);
    printf("re = %f, im = %f\n", p.re, p.im);

    float amplitude = sqrtf( p.re * p.re + p.im * p.im ); /* √(re² + im²) */
    float phase_deg = atan2f(p.im, p.re) * 360.0f / TWO_PI; /* atan2f, converted to degrees */
    
    printf("amplitude = %f, phase = %f degrees\n", amplitude, phase_deg);

    return 0;
}
