#ifndef DSP_UTILS_H
#define DSP_UTILS_H

#include <stdint.h>
#include <stddef.h>

float dsp_rms_i16(const int16_t *samples, size_t count);

#endif  // DSP_UTILS_H
