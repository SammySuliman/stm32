# Firmware Skeleton

This folder mirrors the STM32CubeIDE `Core/` layout so you can drop it into a
CubeMX-generated project.

## How to integrate
1. Use STM32CubeMX to create a project for B-L475E-IOT01A.
2. Enable DFSDM for both MEMS microphones and set DMA in circular mode.
3. Enable I2S for audio output and configure DMA in circular mode.
4. Copy the contents of `Core/Inc` and `Core/Src` into your Cube project.
5. Hook the HAL callbacks in `audio_hw.c` to the generated DMA callbacks.

## Key files
- `Core/Src/audio_capture.c` DMA frame handling
- `Core/Src/audio_pipeline.c` DSP pipeline per frame
- `Core/Src/audio_hw.c` HAL integration points (TODOs)
