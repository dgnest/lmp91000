import serial
import time
import sys

from serialport import get_open_port


def setup():
    port = get_open_port()
    ser = serial.Serial(port, 9600, timeout=1)
    time.sleep(2)
    return ser


def send_cmd(cmd):
    ser.write(cmd + "E")
    line = ser.readline()
    print line


if __name__ == '__main__':
    ser = setup()
    while True:
        cmd = raw_input(
            "Enter commands [w:write / r:read / a:read analog data / q:quit]: "
        )
        if cmd == 'r':
            send_cmd('S00ss')
        if cmd == 'w':
            send_cmd('S2345')
        if cmd == 'a':
            send_cmd('S1a1f')
        if cmd == 'q':
            break
    try:
        ser.close()
        print "\nPort closed. Bye..."
    except:
        print "\nPort couldn't be closed!"
