# Robot Platform

The Robot Platform was initially created in 2019 by a group of students (Jason, Logan, Cade, and David) as part of their capstone project at Massey University's School of Food and Advanced Technology (SF & AT).

Here, I will document what I have done to "revive" the project.

## Aims

I want to:
* Use the robot to support my teaching of the Robot Operating System (ROS) in the robotics course.

## Objectives

I want to:
* Install Ubuntu 22.04 on the Raspberry Pi and use ROS Humble Hawksbill
* Write my own software for the Arduino Nanos.
* Write my own software for the Raspberry Pi.
* Connect a Bluetooth, or equivalent, controller to the Raspberry Pi and remotely control the robot.
* I want to make use of the existing framework and avoid having to build anything.

## Resources

I found the following links helpful:

* http://www.modularcircuits.com/blog/articles/h-bridge-secrets/h-bridge_drivers/

## Step 1

I have created a project named 01_blink. See [here](./01_blink/main.ino). This will blink the Nano's LED. This project is used to validate that the Nano works.

Notes:

The Nanos used in the robot are clones and require the old bootloader to be used when programming. If you use the new bootloader, the program won't upload.

## Step 2

I have created a project named 02_ping. See [here](./02_ping/main.ino). This will create a UDP server, which will return "OK" to the sender when a message is received. There is a Python notebook that can be used to test the project with. The project is used to validate that the ethernet shield works.

Notes:

I manually set my USB-Ethernet adapter's TCP/IPv4 settings to:
* IP address: 192.168.137.2
* Subnet mask: 255.255.255.0
* Default gateway: 192.168.137.1
* Preferred DNS server: 8.8.8.8
* Alternate DNS server: 4.4.4.4

## Step 3

I want to flash my Raspberry Pi with Ubuntu 22.04 and connect it to my Windows PC.

To flash the Raspberry Pi, I used Raspberry PI Imager. See [here](https://www.raspberrypi.com/software/).

Notes:

I used a USB flash drive to install Ubuntu 22.04. I found, after trying multiple SD cards, booting (and using) Ubuntu from USB was much faster and less issue-prone.  

Ubuntu's username and password were set to:
* Username: fknoble
* Password: fknoble

I manually set Ubuntu's Ethernet TCP/IPv4 settings to:
* IP address: 192.168.137.3
* Subnet mask: 255.255.255.0
* Default gateway: 192.168.137.1
* Preferred DNS server: 8.8.8.8
* Alternate DNS server: 4.4.4.4

I installed OpenSSH-server to enable SSH. I typed the following command:
```
sudo apt install openssh-server
```

I used to SSH to remotely connect to Ubuntu. I typed the following command:
```
ssh fknoble@192.168.137.2
```

## Step 4

I want to use a PS4 controller to control the robot. 

Pi My Life Up has a guide on how to connect a PS4 controller to the RPi. See [here](https://pimylifeup.com/raspberry-pi-playstation-controllers/).

Notes:

I typed the following commands to get everything to work:

```
sudo bluetoothctl
agent on
default-agent
scan on // press PS button and Share button
connect YOUR_MAC_ADDRESS // type MAC address of controller
trust YOUR_MAC_ADDRESS // type MAC address of controller
sudo apt install joystick
sudo jstest /dev/input/js0
```

## Step 5

I have created a project named 03_controller. See [here](./03_controller/main.py). This will display the buttons pressed on the PS4 controller.This project is used to validate that the PS4 controller works.

Notes:

Here are the key names and their initial states:
(initial)a released // x
(initial)b released // 0
(initial)x released // square
(initial)y released // triangle
(initial)tl released
(initial)tr released
(initial)tl2 released
(initial)tr2 released
(initial)select released
(initial)start released
(initial)mode released
(initial)thumbl released
(initial)thumbr released
(initial)x: 0.000
(initial)y: 0.000
(initial)z: -1.000
(initial)rx: 0.000
(initial)ry: 0.000
(initial)rz: -1.000
(initial)hat0x: 0.000
(initial)hat0y: 0.000

## Step 6

I want to install ROS with Ubuntu 22.04 to control the robot.

To install ROS, I followed the Debian installation instructions. See [here](https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debians.html).

Notes:

Everying installed okay. 

## Step 7

I have created a project named 04_node. See [here](./04_node/main.py). This will publish the buttons pressed on the PS4 controller to the topic /joystick. This project is used to validate that ROS can get the controller's values and use them to control the motors.

Notes:

Everyhting worked okay.
