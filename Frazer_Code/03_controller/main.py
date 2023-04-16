import os 
import sys

import array
import struct

from fcntl import ioctl

axis_names = {
    0x00: 'x',
    0x01: 'y',
    0x02: 'z',
    0x03: 'rx',
    0x04: 'ry',
    0x05: 'rz',
    0x06: 'throttle',
    0x07: 'rudder',
    0x08: 'wheel',
    0x09: 'gas',
    0x0a: 'brake',
    0x10: 'hat0x',
    0x11: 'hat0y',
    0x12: 'hat1x',
    0x13: 'hat1y',
    0x14: 'hat2x',
    0x15: 'hat2y',
    0x16: 'hat3x',
    0x17: 'hat3y',
    0x18: 'pressure',
    0x19: 'distance',
    0x1a: 'tilt_x',
    0x1b: 'tilt_y',
    0x1c: 'tool_width',
    0x20: 'volume',
    0x28: 'misc',
}

button_names = {
    0x120: 'trigger',
    0x121: 'thumb',
    0x122: 'thumb2',
    0x123: 'top',
    0x124: 'top2',
    0x125: 'pinkie',
    0x126: 'base',
    0x127: 'base2',
    0x128: 'base3',
    0x129: 'base4',
    0x12a: 'base5',
    0x12b: 'base6',
    0x12f: 'dead',
    0x130: 'a',
    0x131: 'b',
    0x132: 'c',
    0x133: 'x',
    0x134: 'y',
    0x135: 'z',
    0x136: 'tl',
    0x137: 'tr',
    0x138: 'tl2',
    0x139: 'tr2',
    0x13a: 'select',
    0x13b: 'start',
    0x13c: 'mode',
    0x13d: 'thumbl',
    0x13e: 'thumbr',

    0x220: 'dpad_up',
    0x221: 'dpad_down',
    0x222: 'dpad_left',
    0x223: 'dpad_right',

    # XBox 360 controller uses these codes.
    0x2c0: 'dpad_left',
    0x2c1: 'dpad_right',
    0x2c2: 'dpad_up',
    0x2c3: 'dpad_down',
}


def main():

    print("Available Devices")

    for fn in os.listdir("/dev/input/"):
        if fn.startswith("js"):
            print("    /dev/input/{}".format(fn))

    fn = "/dev/input/js0"

    print("Opening {}".format(fn))

    jsdev = open(fn, 'rb')

    buf = array.array('B', [0]*64)

    ioctl(jsdev, 0x80006a13 + (0x10000 * len(buf)), buf)

    js_name = buf.tobytes().strip(b'\x00').decode()

    print(js_name)

    buf = array.array('B', [0]*1)

    ioctl(jsdev, 0x80016a11, buf)

    num_axes = buf[0]

    print(num_axes)

    buf = array.array('B', [0]*1)

    ioctl(jsdev, 0x80016a12, buf)

    num_buttons = buf[0]

    print(num_buttons)

    buf = array.array('B', [0]*64)

    ioctl(jsdev, 0x80406a32, buf)

    axis_map = []
    axis_states = []
    for axis in buf[:num_axes]:
        axis_name = axis_names.get(axis)
        axis_map.append(axis_name)
        axis_states.append(0)

        print("{}: {}".format(hex(axis), axis_name))
        
    buf = array.array('H', [0]*64)

    ioctl(jsdev, 0x80406a34, buf)

    btn_map = []
    btn_states = []

    for btn in buf[:num_buttons]:
        btn_name = button_names.get(btn)
        btn_map.append(btn_name)
        btn_states.append(0)

        print("{}: {}".format(hex(btn), btn_name))

    while True:
        evbuf = jsdev.read(8)

        if evbuf:
            time, value, type, number  = struct.unpack('IhBB', evbuf)

            if type & 0x80:
                print("(initial)", end="")

            if type & 0x01:
                btn = btn_map[number]
                if btn:
                    # btn_states[btn] = value
                    btn_states[number] = value
                    if value:
                        print("{} pressed".format(btn))
                    else:
                        print("{} released".format(btn))
            
            if type & 0x02:
                axis = axis_map[number]
                if axis:
                    fvalue = value / 32767.0
                    # axis_states[axis] = fvalue
                    axis_states[number] = fvalue
                    print("{}: {:.3f}".format(axis, fvalue))

    print("Closing {}".format(fn))

    jsdev.close()

    return 0


if __name__ == "__main__":

    sys.exit(main())
