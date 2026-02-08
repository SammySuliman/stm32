## UART audio streaming

This setup streams mono 16 kHz, 16-bit PCM over the ST-LINK virtual COM port.

### MCU setup
- `USART1` baud is set to `1,000,000`.
- Frames are sent from the main loop using a simple header:
  - Sync: `0x55 0xAA`
  - Length: 16-bit little-endian payload size in bytes
  - Counter: 8-bit frame counter
  - Payload: raw PCM samples (mono, 16-bit little-endian)

### PC setup
1. Install Python dependency:
   - `pip install pyserial`
2. Run the receiver:
   - `python tools/uart_audio_rx.py COM5 -b 1000000 -t 10 -o capture.raw`
3. Play captured audio:
   - `ffplay -f s16le -ar 16000 -ac 1 capture.raw`

### Notes
- If you see dropouts, lower the capture duration or ensure the baud rate is stable.
- This is raw PCM without headers; use the exact `ffplay` command above.
