# Hardware Notes

## Board
- STM32L4 Discovery IoT Node (B-L475E-IOT01A)
- MCU: ARM Cortex-M4F
- Onboard dual digital MEMS microphones (PDM)
- DFSDM peripheral for audio capture

## External DAC
PCM5102 I2S DAC for headphone output.

Suggested wiring (set your pin mapping in CubeMX):
- I2S SCK  -> PCM5102 BCK
- I2S WS   -> PCM5102 LRCK
- I2S SD   -> PCM5102 DIN
- GND      -> GND
- 3.3V     -> VCC

## Power and grounding
Keep the analog ground and headphone wiring short. If you hear noise, add a
small RC filter at the output or increase analog power decoupling at the DAC.
