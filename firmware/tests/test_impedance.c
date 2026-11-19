/* impedance test */
#include <stdio.h>
#include <math.h>
#include "impedance.h"

#define PI	    3.14159265f
#define TWO_PI      6.28318531f
#define N           64      	/* number of samples */
#define M           16      	/* samples per cycle (so 4 cycles) */
#define OFFSET      2048.0f 	/* mid-scale of the 12-bit ADC */
#define AMPLITUDE   1000.0f
#define PHASE  	    0.5236f 	/* 30 degrees, in radians */

static void print_phasor(const char *name, phasor_t p)
{
    /* amplitude and phase_deg*/
    float amplitude = sqrtf(p.re * p.re + p.im * p.im);
    float phase_deg = atan2f(p.im, p.re) * 360.0f / TWO_PI;
    printf("%s: amplitude = %f, phase = %f degrees\n", name, amplitude, phase_deg);
}

int main(void)
{
    uint16_t samples[N];
    for (uint32_t i = 0; i < N; i++) {
    	samples[i] = (uint16_t)(OFFSET + AMPLITUDE * cosf(TWO_PI * i / M + PHASE));
    }
    phasor_t p = phasor_from_samples(samples, N, 1, M);
    printf("re = %f, im = %f\n", p.re, p.im);
    
    print_phasor("single", p);
    
    uint16_t both[2 * N];
    for (uint32_t i = 0; i < N; i++) {
	both[2 * i]     = (uint16_t)(OFFSET + 1000.0f * cosf(TWO_PI * i / M));
	both[2 * i + 1] = (uint16_t)(OFFSET + 500.0f  * cosf(TWO_PI * i / M + PHASE)); 
    }

    phasor_t a = phasor_from_samples(both,     N, 2, M);
    phasor_t b = phasor_from_samples(&both[1], N, 2, M);

    print_phasor("A", a);
    print_phasor("B", b);
    
    uint16_t res[2 * N];
    for (uint32_t i = 0; i < N; i++) {
	res[2 * i]     = (uint16_t)(OFFSET + 1000.0f * cosf(TWO_PI * i / M));
	res[2 * i + 1] = (uint16_t)(OFFSET + 500.0f  * cosf(TWO_PI * i / M + PI)); 
    }

    phasor_t v_in  = phasor_from_samples(res,     N, 2, M);
    phasor_t v_out = phasor_from_samples(&res[1], N, 2, M);
    impedance_t z  = impedance_from_phasors(v_in, v_out, 1000.0f);

    printf("resistor: r = %f, x = %f\n", z.r, z.x);

    uint16_t cap[2 * N];
    for (uint32_t i = 0; i < N; i++) {
	cap[2 * i]         = (uint16_t)(OFFSET + 1000.0f * cosf(TWO_PI * i / M));
	cap[2 * i + 1]     = (uint16_t)(OFFSET + 295.3f * cosf(TWO_PI * i / M - PI / 2));
    }

    phasor_t c_in  = phasor_from_samples(cap,     N, 2, M);
    phasor_t c_out = phasor_from_samples(&cap[1], N, 2, M);
    impedance_t zc = impedance_from_phasors(c_in, c_out, 1000.0f);

    printf("capacitors: C = %e F\n", capacitance_from_z(zc, 1000.0f));

    return 0;
}
