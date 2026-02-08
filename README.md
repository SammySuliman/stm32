# Assistive Listening on STM32L4

Real-time, low-latency assistive listening firmware for the STM32L4 Discovery IoT
Node (B-L475E-IOT01A). The system captures audio from the two onboard MEMS
microphones (PDM), converts to 16-bit PCM at 16 kHz using DFSDM + DMA, and applies
an embedded DSP pipeline for noise suppression.

## Quick start
- Open `firmware/` in STM32CubeIDE.
- Use CubeMX to generate the DFSDM + DMA init code for the
  B-L475E-IOT01A board.
- Build and flash.
- To stream captured audio to a PC over UART, see `docs/uart-streaming.md`.

## Repository layout
- `docs/` system architecture and hardware notes.
- `firmware/` STM32CubeIDE-style firmware skeleton.

## Key design targets
- 16 kHz stereo capture from DFSDM.
- 10 ms frames (160 samples) for low latency.
- Lightweight time-domain noise suppression.

## Notes
This is a firmware scaffold that includes the DSP pipeline and the interfaces
needed for DFSDM and I2S integration. It is intended to be completed by
generating board-specific initialization with STM32CubeMX and by connecting the
HAL callbacks to the functions in `firmware/Core/Src/audio_hw.c`.
