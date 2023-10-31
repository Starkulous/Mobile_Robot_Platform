# Mobile_Robot_Platform
Capstone Project Year 4

The Robot Platform was created in 2023 by a group of students (Joe, Hannah, Inuka and Rebecca) as part of their capstone project at Massey University's School of Food and Advanced Technology (SF & AT).

The folder Fazer_Code has previous code from the intial version of this system and Here, is the documentation of the progress and what has been changed to the code.

## Aims

I want to:
* Develop a robotic platform that is robust and can be controlled.

## Objectives

I want to:
* Install Ubuntu 20.04 on the Jetson nano and Ros Foxy.
* Write my own software for the Jetson nano.
* Connect a Bluetooth, or equivalent, controller to the Jetson nano and remotely control the robot.

## Resources

I found the following links helpful:

* Boot from USB: https://www.youtube.com/watch?v=53rRMr1IpWs&t=0s
* install 20.04 version of ubuntu https://www.youtube.com/watch?v=MMzNxJvYP2A
* ROS Foxy Install: https://docs.ros.org/en/foxy/Installation.html
* Jetson Nano inital OS: https://developer.nvidia.com/embedded/learn/get-started-jetson-nano-devkit#write
* Linux Script setup: https://forums.developer.nvidia.com/t/how-to-run-a-script-on-boot/108411/3

## Step 1

Using the link above I installed the intial Jetson OS on an SD card with Raspberry pi imager, which has ubuntu version 18.04 and upgraded it to 20.04 using another link above.

## Step 2

I moved the OS to a USB and had the Jetson boot from this as it was more reliable and much quicker to read and write to the Jetson.

Ubuntu's username and password were set to:
* Username: joe
* Password: robotjoe1

I manually set Ubuntu's Ethernet TCP/IPv4 settings to:
* IP address: 192.168.137.2
* Subnet mask: 255.255.255.0
* Default gateway: 192.168.137.1
* Preferred DNS server: 8.8.8.8
* Alternate DNS server: 4.4.4.4

The nanos on the motor drivers have the Ip address: 192.168.137.3 and mac address {0x00 0x00 0x00 0x00 0x00 0x03} and 192.168.137.4 and mac address {0x00 0x00 0x00 0x00 0x00 0x04} respectivly.

## Step 3

I then installed ROS Foxy using the link above.

## Step 4

I want to use an xbox controller to control the robot. 

Todo this I added a bluetooth module to the jetson that had a usb extension cable attached as this stopped the EMF shielding from blocking the signal.

Notes:
I first set the Xbox controller into searching mode by pressing the button on the top of the controller and wait for it to blink.

I typed the following commands to allow the connection:

```
sudo sh -c 'echo 1 >/sys/module/bluetooth/parameters/disable_ertm'
```

I then connected to the xbox controller through the bluetooth settings and setup auto connection so i only do this once.

## Step 5

I have used a project named 04_node seen in the frazer_code folder. This will publish the buttons pressed on the Xbox controller to the topic /joystick. This project is used to validate that ROS can get the controller's values and use them to control the motors.

## Step 6

In the ROS_System folder we can see version one contains the above files but with the joystick.py folder edited to send a command to the motor drivers through UDP once a specific button is pressed.

## Step 7 
To run this system I used the lauch commmand: ros2 launch py_pubsub robot_launch.py

## Other Versions
Version 2 - Contains changes that allow the controller to change the PWM of the motors
Version 3 - Contains a linux service that runs on start up so no monitors or keyboards are needed to start the system just power on.
Version 4 - Final Version, Uses TCP instead of UDP to send commands to motor drivers prioritizing Accuracy over speed. 




