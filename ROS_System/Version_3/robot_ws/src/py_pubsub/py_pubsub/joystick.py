import os
import sys

import array
import struct

from fcntl import ioctl

import rclpy

from rclpy.node import Node
from std_msgs.msg import Float32MultiArray

verbose = False

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

class JoystickPublisher(Node):
    def __init__(self):
        super().__init__('joystick')

        if verbose:
            self.get_logger().info("Available Devices")

            for fn in os.listdir("/dev/input/"):
                if fn.startswith("js"):
                    self.get_logger().info("    /dev/input/{}".format(fn))

        self.fn = "/dev/input/js0"

        if verbose:
            self.get_logger().info("Opening {}".format(self.fn))

        self.jsdev = open(self.fn, 'rb')

        buf = array.array('B', [0]*64)

        ioctl(self.jsdev, 0x80006a13 + (0x10000 * len(buf)), buf)

        self.js_name = buf.tobytes().strip(b'\x00').decode()

        if verbose:
            self.get_logger().info("{}".format(self.js_name))

        buf = array.array('B', [0]*1)

        ioctl(self.jsdev, 0x80016a11, buf)

        self.num_axes = buf[0]

        if verbose:
            self.get_logger().info("{}".format(self.num_axes))

        buf = array.array('B', [0]*1)

        ioctl(self.jsdev, 0x80016a12, buf)

        self.num_buttons = buf[0]

        if verbose:
            self.get_logger().info("{}".format(self.num_buttons))

        buf = array.array('B', [0]*64)

        ioctl(self.jsdev, 0x80406a32, buf)

        self.axis_map = []
        self.axis_states = []
        for axis in buf[:self.num_axes]:
            axis_name = axis_names.get(axis)
            self.axis_map.append(axis_name)
            self.axis_states.append(0)
        
            if verbose:
                self.get_logger().info("{}: {}".format(hex(axis), axis_name))

        buf = array.array('H', [0]*64)

        ioctl(self.jsdev, 0x80406a34, buf)

        self.btn_map = []
        self.btn_states = []

        for btn in buf[:self.num_buttons]:
            btn_name = button_names.get(btn)
            self.btn_map.append(btn_name)
            self.btn_states.append(0)

            if verbose:
                self.get_logger().info("{}: {}".format(hex(btn), btn_name))

        self.publisher = self.create_publisher(Float32MultiArray, 'joystick', 10)

        timer_period = 0.03
        
        self.timer = self.create_timer(timer_period, self.timer_callback)

        return

    def timer_callback(self):

        evbuf = self.jsdev.read(8)

        if evbuf:
            time, value, type, number  = struct.unpack('IhBB', evbuf)
                        
            if type & 0x80:
                self.get_logger().info("(initial)")

            if type & 0x01:
                btn = self.btn_map[number]
                if btn:
                    self.btn_states[number] = value
                    if value:
                        self.get_logger().info("{} pressed".format(btn))
                    else:
                        self.get_logger().info("{} released".format(btn))
            
            if type & 0x02:
                axis = self.axis_map[number]
                if axis:
                    fvalue = value / 32767.0
                    self.axis_states[number] = fvalue
                    self.get_logger().info("{}: {:.3f}".format(axis, fvalue))
            
        msg = Float32MultiArray()
        msg.data = [float(i) for i in self.btn_states]
        self.publisher.publish(msg)

        return

    def __del__(self):

        self.jsdev.close()

        return




def main(args=None):

    rclpy.init(args=args)

    joystick_publisher = JoystickPublisher()

    rclpy.spin(joystick_publisher)

    joystick_publisher.destroy_node()

    rclpy.shutdown()

    return 0


if __name__ == "__main__":

    sys.exit(main())