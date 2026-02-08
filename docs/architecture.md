# System Architecture

## Signal flow
MEMS microphones (PDM) ->
DFSDM + DMA ->
16-bit PCM frames ->
DSP pipeline ->
I2S ->
PCM5102 DAC ->
Headphones

## Frame timing
- Sample rate: 16 kHz
- Frame size: 10 ms
- Samples per frame: 160
- Stereo interleaved input buffer

## DSP pipeline
1. Time-domain noise suppression
   - Frame RMS tracking per channel
   - Noise floor estimation
   - Gain reduction for low SNR frames
2. Stereo passthrough
   - Processed left/right channels remain interleaved

## Latency
The pipeline is designed to run per 10 ms frame with a single-frame algorithmic
delay. The DMA buffering is structured as double buffers to keep latency low.
