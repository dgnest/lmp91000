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
            # Send Init + command bytes.
            ser.write("Sr")
            # Sensor id.
            ser.write(chr(1))
            # Address.
            ser.write(chr(0x10))
            # Value.
            ser.write(chr(0x00))
            # Send stop byte.
            ser.write("E")
        if cmd == 'w':
            # send_cmd('Sw045')

            # Send Init + command bytes.
            ser.write('S')
            ser.write('w')
            # Sensor id.
            ser.write(chr(1))
            # Address.
            ser.write(chr(0x10))
            # Value.
            ser.write(chr(0xFF))
            # Send stop byte
            ser.write('E')
        if cmd == 'a':
            send_cmd('Sa01f')
        if cmd == 'q':
            break
        
        line = ser.readline()
        print line
    try:
        ser.close()
        print "\nPort closed. Bye..."
    except:
        print "\nPort couldn't be closed!"
