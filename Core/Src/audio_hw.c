#include "audio_hw.h"

#include "app_config.h"
#include "audio_capture.h"

#ifdef USE_HAL_DRIVER
#include "main.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_dfsdm.h"
#endif

#ifdef USE_HAL_DRIVER
extern DFSDM_Filter_HandleTypeDef hdfsdm1_filter1;
extern DFSDM_Channel_HandleTypeDef hdfsdm1_channel1;
#endif

static int32_t g_dfsdm_raw[AUDIO_FRAME_SAMPLES * AUDIO_DMA_FRAMES];
static int16_t g_capture_buffer[AUDIO_DMA_SAMPLES];

int16_t *audio_hw_get_capture_buffer(void) {
  return g_capture_buffer;
}

void audio_hw_init(void) {
  // DFSDM + DMA are initialized by CubeMX-generated code.
}

//void audio_hw_start(void) {
//#ifdef USE_HAL_DRIVER
//  if (HAL_DFSDM_FilterRegularStart_DMA(&hdfsdm1_filter1,
//                                       g_dfsdm_raw,
//                                       AUDIO_FRAME_SAMPLES * AUDIO_DMA_FRAMES) != HAL_OK) {
//    Error_Handler();
//  }
//#endif
//}

void audio_hw_start(void) {
#ifdef USE_HAL_DRIVER
  HAL_StatusTypeDef status =
      HAL_DFSDM_FilterRegularStart_DMA(&hdfsdm1_filter1,
                                       g_dfsdm_raw,
                                       AUDIO_FRAME_SAMPLES * AUDIO_DMA_FRAMES);

  if (status != HAL_OK) {
      volatile int err = status;  // put breakpoint here
      Error_Handler();
  }
#endif
}


void audio_hw_submit_frame(const int16_t *interleaved,
                           size_t frame_samples) {
  (void)interleaved;
  (void)frame_samples;
  // Audio output disabled (SAI removed).
}

#ifdef USE_HAL_DRIVER
static int16_t clamp_i16(int32_t value) {
  if (value > 32767) {
    return 32767;
  }
  if (value < -32768) {
    return -32768;
  }
  return (int16_t)value;
}

static void dfsdm_to_interleaved(const int32_t *src,
                                 int16_t *dst,
                                 size_t samples) {
  for (size_t i = 0; i < samples; ++i) {
    int32_t shifted = src[i] >> 8;
    int16_t sample = clamp_i16(shifted);
    dst[i * 2U] = sample;
    dst[i * 2U + 1U] = sample;
  }
}

// Hook these into the CubeMX-generated DFSDM callbacks.
void HAL_DFSDM_FilterRegConvHalfCpltCallback(DFSDM_Filter_HandleTypeDef *hdfsdm) {
  (void)hdfsdm;
  dfsdm_to_interleaved(g_dfsdm_raw,
                       g_capture_buffer,
                       AUDIO_FRAME_SAMPLES);
  audio_capture_on_dma_half(g_capture_buffer);
}

void HAL_DFSDM_FilterRegConvCpltCallback(DFSDM_Filter_HandleTypeDef *hdfsdm) {
  (void)hdfsdm;
  dfsdm_to_interleaved(&g_dfsdm_raw[AUDIO_FRAME_SAMPLES],
                       &g_capture_buffer[AUDIO_FRAME_SAMPLES * AUDIO_CHANNELS],
                       AUDIO_FRAME_SAMPLES);
  audio_capture_on_dma_full(&g_capture_buffer[AUDIO_FRAME_SAMPLES * AUDIO_CHANNELS]);
}

#endif
