/* impedance.h */
#ifndef IMPEDANCE_H
#define IMPEDANCE_H

#include <stdint.h>

typedef struct {
	float re; /* real part, in-phase (cos) */
	float im; /* imaginary part, quadrature (sin) */
} phasor_t;

typedef struct {
	float r; /* resistance, the real part, in ohms */
	float x; /* reactance, the imaginary part, in ohms */
} impedance_t;

/* this works out the phasor (amplitude & phase) of a sine wave from the ADC samples
   samples is a pointer to the first sample of the channel, 'n' is the number of samples and must be a whole number of cycles
   stride is the distance between this channel's samples (2 if interleaved)
   samples_per_cycle samples in one cycle of the test signal
   returns phasor_t, with re & im in the ADC counts */
phasor_t phasor_from_samples(const uint16_t *samples, uint32_t n, uint32_t stride, uint32_t samples_per_cycle);

/* using Dave's auto-balancing bridge from, D. Pearce, "Measuring Components Two" Lecture, Slide 5. Inverting Amplifier
   gain V_out/V_in = -R_f / Z, so Z = -R_f * V_in / V_out
   returns impedance_t, with r and x in ohms */
impedance_t impedance_from_phasors(phasor_t v_in, phasor_t v_out, float r_f);

/* works out capacitance from the impedance, C = -1 / (w * X), w = 2*pi*freq
   returns capacitance in farads */
float capacitance_from_z(impedance_t z, float freq);

/* works out inductance from the impedance, L = X / w, w = 2*pi*freq
   returns inductance in henries */
float inductance_from_z(impedance_t z, float freq);
#endif
