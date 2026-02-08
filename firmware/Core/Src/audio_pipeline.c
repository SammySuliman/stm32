#include "audio_pipeline.h"

#include "app_config.h"
#include "dsp_noise_suppressor.h"

static audio_pipeline_config_t g_config;

static int16_t g_left_frame[AUDIO_FRAME_SAMPLES];
static int16_t g_right_frame[AUDIO_FRAME_SAMPLES];
static noise_suppressor_state_t g_noise_state_left;
static noise_suppressor_state_t g_noise_state_right;

void audio_pipeline_init(const audio_pipeline_config_t *config) {
  g_config = *config;

  noise_suppressor_init(&g_noise_state_left,
                        NOISE_FLOOR_ALPHA,
                        NOISE_GATE_RATIO,
                        MIN_OUTPUT_GAIN);
  noise_suppressor_init(&g_noise_state_right,
                        NOISE_FLOOR_ALPHA,
                        NOISE_GATE_RATIO,
                        MIN_OUTPUT_GAIN);
}

void audio_pipeline_process_frame(const int16_t *input_interleaved,
                                  int16_t *output_interleaved,
                                  size_t frame_samples) {
  if (frame_samples > AUDIO_FRAME_SAMPLES) {
    frame_samples = AUDIO_FRAME_SAMPLES;
  }

  for (size_t i = 0; i < frame_samples; ++i) {
    g_left_frame[i] = input_interleaved[i * 2U];
    g_right_frame[i] = input_interleaved[i * 2U + 1U];
  }
  noise_suppressor_process(&g_noise_state_left, g_left_frame, frame_samples);
  noise_suppressor_process(&g_noise_state_right, g_right_frame, frame_samples);

  for (size_t i = 0; i < frame_samples; ++i) {
    output_interleaved[i * 2U] = g_left_frame[i];
    output_interleaved[i * 2U + 1U] = g_right_frame[i];
  }
}
