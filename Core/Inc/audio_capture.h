#ifndef AUDIO_CAPTURE_H
#define AUDIO_CAPTURE_H

#include <stdint.h>
#include <stddef.h>

typedef void (*audio_frame_callback_t)(const int16_t *interleaved,
                                       size_t frame_samples);

void audio_capture_init(audio_frame_callback_t callback);
void audio_capture_start(void);

// To be called from DMA half/full callbacks.
void audio_capture_on_dma_half(const int16_t *buffer);
void audio_capture_on_dma_full(const int16_t *buffer);

// Copy the most recent captured frame into dst.
// Returns number of samples per channel copied, or 0 if no frame yet.
size_t audio_capture_read_latest(int16_t *dst_interleaved,
                                 size_t max_frame_samples);

// Returns a monotonically increasing sequence counter for captured frames.
uint32_t audio_capture_latest_sequence(void);

#endif  // AUDIO_CAPTURE_H
