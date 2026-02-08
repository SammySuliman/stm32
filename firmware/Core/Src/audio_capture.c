#include "audio_capture.h"

#include "app_config.h"
#include "audio_hw.h"

static audio_frame_callback_t g_frame_callback = 0;

void audio_capture_init(audio_frame_callback_t callback) {
  g_frame_callback = callback;
}

void audio_capture_start(void) {
  // Starts DFSDM + DMA via the hardware layer.
  audio_hw_start();
}

static void handle_dma_frame(const int16_t *buffer) {
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
