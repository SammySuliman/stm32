#ifndef AUDIO_PIPELINE_H
#define AUDIO_PIPELINE_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
  uint32_t sample_rate_hz;
  uint32_t frame_samples;
} audio_pipeline_config_t;

void audio_pipeline_init(const audio_pipeline_config_t *config);

// Process one frame of interleaved stereo samples.
// Input and output may alias.
void audio_pipeline_process_frame(const int16_t *input_interleaved,
                                  int16_t *output_interleaved,
                                  size_t frame_samples);

#endif  // AUDIO_PIPELINE_H
