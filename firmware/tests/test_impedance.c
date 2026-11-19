/* impedance test */
#include <stdio.h>
#include <math.h>
#include "impedance.h"

#define TWO_PI      6.28318531f
#define N           64      /* number of samples */
#define M           16      /* samples per cycle (so 4 cycles) */
#define OFFSET      2048.0f /* mid-scale of the 12-bit ADC */
#define AMPLITUDE   1000.0f

int main(void)
{
    uint16_t samples[N];
    for (uint32_t i = 0; i < N; i++) {
    	samples[i] = (uint16_t)(OFFSET + AMPLITUDE * cosf(TWO_PI * i / M));
    }
    phasor_t p = phasor_from_samples(samples, N, 1, M);
    printf("re = %f, im = %f\n", p.re, p.im);
    return 0;
}
