# Firmware Plan

## Capture
- DFSDM + DMA for stereo PDM capture.
- Decimate to 16 kHz, 16-bit PCM.
- Use double-buffer DMA callbacks for 10 ms frames.

## DSP
- Noise suppressor: RMS-based noise floor estimator per channel.
- Output: stereo preserved for I2S.

## Output
- I2S with DMA feeding the PCM5102 DAC.
- Buffering aligned to 10 ms frames.

## Integration
- Use STM32CubeMX to configure DFSDM + I2S + DMA.
- Connect HAL DMA callbacks to the handlers in `audio_hw.c`.
