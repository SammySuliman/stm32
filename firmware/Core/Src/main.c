#include "app_config.h"
#include "audio_capture.h"
#include "audio_hw.h"
#include "audio_pipeline.h"

#ifdef USE_HAL_DRIVER
#include "stm32l4xx_hal.h"
#endif

static int16_t g_output_frame[AUDIO_FRAME_SAMPLES * AUDIO_CHANNELS];

void SystemClock_Config(void);

static void on_audio_frame(const int16_t *interleaved, size_t frame_samples) {
  audio_pipeline_process_frame(interleaved, g_output_frame, frame_samples);
  audio_hw_submit_frame(g_output_frame, frame_samples);
}

int main(void) {
#ifdef USE_HAL_DRIVER
  HAL_Init();
  SystemClock_Config();
#endif

  audio_hw_init();

  audio_pipeline_config_t config = {
      .sample_rate_hz = AUDIO_SAMPLE_RATE_HZ,
      .frame_samples = AUDIO_FRAME_SAMPLES,
  };
  audio_pipeline_init(&config);

  audio_capture_init(on_audio_frame);
  audio_capture_start();

  while (1) {
#ifdef USE_HAL_DRIVER
    __WFI();
#endif
  }
}
