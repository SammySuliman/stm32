#include "audio_capture.h"

#include <string.h>

#include "app_config.h"
#include "audio_hw.h"

static audio_frame_callback_t g_frame_callback = 0;
static int16_t g_latest_frame[AUDIO_FRAME_SAMPLES * AUDIO_CHANNELS];
static volatile uint32_t g_latest_seq = 0;
static volatile uint8_t g_has_frame = 0;

void audio_capture_init(audio_frame_callback_t callback) {
  g_frame_callback = callback;
}

void audio_capture_start(void) {
  // Starts DFSDM + DMA via the hardware layer.
  audio_hw_start();
}

static void handle_dma_frame(const int16_t *buffer) {
  g_latest_seq++;
  memcpy(g_latest_frame,
         buffer,
         sizeof(int16_t) * AUDIO_FRAME_SAMPLES * AUDIO_CHANNELS);
  g_latest_seq++;
  g_has_frame = 1;

  if (g_frame_callback) {
    g_frame_callback(buffer, AUDIO_FRAME_SAMPLES);
  }
}

void audio_capture_on_dma_half(const int16_t *buffer) {
  handle_dma_frame(buffer);
}

void audio_capture_on_dma_full(const int16_t *buffer) {
  handle_dma_frame(buffer);
}

size_t audio_capture_read_latest(int16_t *dst_interleaved,
                                 size_t max_frame_samples) {
  if (!dst_interleaved || !g_has_frame) {
    return 0;
  }

  size_t frame_samples = AUDIO_FRAME_SAMPLES;
  if (max_frame_samples < frame_samples) {
    frame_samples = max_frame_samples;
  }

  const size_t total_samples = frame_samples * AUDIO_CHANNELS;
  uint32_t seq_start = 0;
  uint32_t seq_end = 0;

  do {
    seq_start = g_latest_seq;
    if (seq_start & 1U) {
      continue;
    }
    memcpy(dst_interleaved,
           g_latest_frame,
           sizeof(int16_t) * total_samples);
    seq_end = g_latest_seq;
  } while (seq_start != seq_end || (seq_start & 1U));

  return frame_samples;
}

uint32_t audio_capture_latest_sequence(void) {
  return g_latest_seq;
}
