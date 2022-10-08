#! /usr/env/python3

import serial
import argparse
import time


def loop(ser:serial.Serial, *args, **kwargs):
    wait_more = kwargs.get("waitime", 0.1)

    if ser.inWaiting() <= 0:
        return

    while ser.inWaiting() < 37:
        time.sleep(wait_more)
        
    print(ser.read_all().decode("utf-8"))
        


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--device', '-d', type=str, default="/dev/ttyAMA1") # port
    parser.add_argument('--rate', '-r', type=int, default=115200) # baudrate
    parser.add_argument('--frequency', '-f', type=int, default=1.) # refresh Hz
    args = parser.parse_args()

    sleep_time = 1 / args.frequency - 0.01
    ser = serial.Serial(args.device, args.rate)

    print("---- Serial Client Start ----")
    print(f"port: {args.device}, baudrate: {args.rate} @ {args.frequency}Hz")
    while True and ser.isOpen():
        loop(ser)
        time.sleep(sleep_time)
    print("Error: can't open serial.")