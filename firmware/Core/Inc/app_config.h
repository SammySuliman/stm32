#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <stdint.h>

// Audio capture configuration
#define AUDIO_SAMPLE_RATE_HZ      16000U
#define AUDIO_FRAME_MS            10U
#define AUDIO_FRAME_SAMPLES       (AUDIO_SAMPLE_RATE_HZ * AUDIO_FRAME_MS / 1000U)
#define AUDIO_CHANNELS            2U

// DMA double buffer (two frames)
#define AUDIO_DMA_FRAMES          2U
#define AUDIO_DMA_SAMPLES         (AUDIO_FRAME_SAMPLES * AUDIO_CHANNELS * AUDIO_DMA_FRAMES)

// Noise suppressor configuration
#define NOISE_FLOOR_ALPHA         0.95f
#define NOISE_GATE_RATIO          1.5f
#define MIN_OUTPUT_GAIN           0.15f

#endif  // APP_CONFIG_H
