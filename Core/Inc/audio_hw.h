#ifndef AUDIO_HW_H
#define AUDIO_HW_H

#include <stdint.h>
#include <stddef.h>

void audio_hw_init(void);
void audio_hw_start(void);

// Submit processed frame to audio output (no-op if output disabled).
void audio_hw_submit_frame(const int16_t *interleaved,
                           size_t frame_samples);

// Provide access to DMA PCM buffer used by DFSDM.
int16_t *audio_hw_get_capture_buffer(void);

#endif  // AUDIO_HW_H
