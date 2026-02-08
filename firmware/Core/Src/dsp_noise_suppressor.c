#include "dsp_noise_suppressor.h"

#include "dsp_utils.h"

void noise_suppressor_init(noise_suppressor_state_t *state,
                           float noise_floor_alpha,
                           float noise_gate_ratio,
                           float min_output_gain) {
  state->noise_floor = 0.0f;
  state->noise_floor_alpha = noise_floor_alpha;
  state->noise_gate_ratio = noise_gate_ratio;
  state->min_output_gain = min_output_gain;
}

void noise_suppressor_process(noise_suppressor_state_t *state,
                              int16_t *samples,
                              size_t count) {
  float rms = dsp_rms_i16(samples, count);
  if (state->noise_floor <= 0.0f) {
    state->noise_floor = rms;
  }

  // Update noise floor when the frame is quiet.
  if (rms < state->noise_floor * state->noise_gate_ratio) {
    state->noise_floor = state->noise_floor_alpha * state->noise_floor +
                         (1.0f - state->noise_floor_alpha) * rms;
  }

  float gain = 1.0f;
  if (rms > 1.0f) {
    float excess = rms - state->noise_floor;
    gain = excess / rms;
  }
  if (gain < state->min_output_gain) {
    gain = state->min_output_gain;
  }

  for (size_t i = 0; i < count; ++i) {
    int32_t value = (int32_t)((float)samples[i] * gain);
    if (value > 32767) {
      value = 32767;
    } else if (value < -32768) {
      value = -32768;
    }
    samples[i] = (int16_t)value;
  }
}
