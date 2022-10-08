#! /usr/env/python3

import serial
import argparse
import time
import random

def loop(ser:serial.Serial, *args, **kwargs):
    info_fn = kwargs.get("info")
    if info_fn is None:
        info_str = time.ctime() + " info %1.4f." % random.random()
        info = info_str.encode("utf-8")
    elif hasattr(info_fn, "__call__"):
        info = info_fn()
    else:
        info = info_fn
    if ser.writable():
        ret = ser.write(info)
        print("write done (%d)." % ret)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--device', '-d', type=str, default="/dev/ttyAMA0") # port
    parser.add_argument('--rate', '-r', type=int, default=115200) # baudrate
    parser.add_argument('--frequency', '-f', type=int, default=1.) # refresh Hz
    args = parser.parse_args()

    sleep_time = 1 / args.frequency
    ser = serial.Serial(args.device, args.rate)

    print("---- Serial Server Start ----")
    print(f"port: {args.device}, baudrate: {args.rate} @ {args.frequency}Hz")
    while True and ser.isOpen():
        loop(ser)
        time.sleep(sleep_time)
    print("Error: can't open serial.")
    