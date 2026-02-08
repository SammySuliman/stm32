#ifndef DSP_NOISE_SUPPRESSOR_H
#define DSP_NOISE_SUPPRESSOR_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
  float noise_floor;
  float noise_floor_alpha;
  float noise_gate_ratio;
  float min_output_gain;
} noise_suppressor_state_t;

void noise_suppressor_init(noise_suppressor_state_t *state,
                           float noise_floor_alpha,
                           float noise_gate_ratio,
                           float min_output_gain);

void noise_suppressor_process(noise_suppressor_state_t *state,
                              int16_t *samples,
                              size_t count);

#endif  // DSP_NOISE_SUPPRESSOR_H
