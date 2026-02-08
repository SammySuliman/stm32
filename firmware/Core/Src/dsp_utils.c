#include "dsp_utils.h"

#include <math.h>

float dsp_rms_i16(const int16_t *samples, size_t count) {
  if (count == 0) {
    return 0.0f;
  }
  double acc = 0.0;
  for (size_t i = 0; i < count; ++i) {
    double s = (double)samples[i];
    acc += s * s;
  }
  double mean = acc / (double)count;
  return (float)sqrt(mean);
}
