#!/usr/bin/env python3
import argparse
import struct
import sys
import time

import serial


SYNC = b"\x55\xAA"
HEADER_SIZE = 5  # sync(2) + len(2) + counter(1)


def read_exact(ser, nbytes):
    data = bytearray()
    while len(data) < nbytes:
        chunk = ser.read(nbytes - len(data))
        if not chunk:
            continue
        data.extend(chunk)
    return bytes(data)


def find_sync(ser):
    window = bytearray()
    while True:
        b = ser.read(1)
        if not b:
            continue
        window += b
        if len(window) > 2:
            window = window[-2:]
        if window == SYNC:
            return


def main():
    parser = argparse.ArgumentParser(description="Receive mono 16kHz PCM over UART.")
    parser.add_argument("port", help="Serial port, e.g. COM5 or /dev/ttyACM0")
    parser.add_argument("-b", "--baud", type=int, default=1000000, help="Baud rate")
    parser.add_argument("-o", "--out", default="capture.raw", help="Output raw file")
    parser.add_argument("-t", "--seconds", type=float, default=5.0, help="Capture duration")
    args = parser.parse_args()

    ser = serial.Serial(args.port, args.baud, timeout=0.1)
    start = time.time()

    with open(args.out, "wb") as f:
        while time.time() - start < args.seconds:
            find_sync(ser)
            header = read_exact(ser, HEADER_SIZE - 2)
            length = header[0] | (header[1] << 8)
            payload = read_exact(ser, length)
            f.write(payload)

    ser.close()
    print(f"Wrote {args.out}")
    print("Play with: ffplay -f s16le -ar 16000 -ac 1 " + args.out)


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        sys.exit(0)
