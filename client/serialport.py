import serial
import time
import sys

from serial.tools.list_ports import comports


def get_open_port():
    ports = zip(*comports())[0]
    for port in ports:
        try:
            ser = serial.Serial(port, 9600, timeout=1)
            time.sleep(2)
            print "Port opened: %s" % port
            ser.close()
            return port
        except:
            continue
    print "There's no port opened!\nClosing connection..."
    sys.exit()


if __name__ == '__main__':
    port = get_open_port()
